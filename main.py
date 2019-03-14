import os
import sqlite3
from contextlib import closing
from flask import Flask, request, session, g, redirect, url_for, abort, \
    render_template, flash

app = Flask(__name__)


app.config.update(

    dict(
        DATABASE=os.path.join(app.root_path, 'flaskr.db'),
        DEBUG=True,
        SECRET_KEY='development key',
        USERNAME='admin',
        PASSWORD='default'
        AMOUNT=0
    ))
app.config.from_envvar('FLASKR_SETTINGS', silent=True)

# 连接部分


def connect_db():
    rv = sqlite3.connect(app.config['DATABASE'])
    rv.row_factory = sqlite3.Row
    return rv
# 初始化部分


def init_db():
    db = get_db()
    with app.open_resource('schema.sql', mode='r') as f:
        db.cursor().executescript(f.read())
    db.commit()


@app.cli.command('initdb')
def initdb_command():
    init_db()
    print('Initialized the database.')


def get_db():
    if not hasattr(g, 'sqlite_db'):
        g.sqlite_db = connect_db()
    return g.sqlite_db


@app.teardown_appcontext
def close_db(error):
    if hasattr(g, 'sqlite_db'):
        g.sqlite_db.close()

# 主页部分


@app.route('/')
def show_entries():

    return render_template('show_entries.html')


@app.route('/regist', methods=['GET', 'POST'])
def regist():
    pass


@app.route('/', methods=['GET', 'POST'])
def show():

    return render_template('show_entries.html', entries=app.config['AMOUNT'])


@app.route('/save', methods=['GET', 'POST'])
def save():
    error = None
    if request.methods == 'POST':
        if not(request.form['money'].isdigit()):
            error = 'Invalid number'
        num = int(10, request.form['money'])
        amount = app.config['AMOUNT']
        if not(num % 50 == 0):
            error = 'Invalid number'
        id = int(10, app.config.USERNAME)
        amount += num
        app.config.update(dict(
            AMOUNT=amount))
        transfer = struct.pack(
            '=20sc2i', app.config['USERNAME'], b'a', num, id, app.config['USERNAME'], app.config['PASSWORD'], app.config['AMOUNT'], )
        return redirect(url_for('show_entries'))
    return render_template('login.html', error=error)


@app.route('/draw', methods=['GET', 'POST'])
def draw():
    error = None
    if request.methods == 'POST':
        if not(request.form['money'].isdigit()):
            error = 'Invalid number'
        num = int(10, request.form['money'])
        amount = app.config['AMOUNT']
        if not(num % 50 == 0):
            error = 'Invalid number'
        id = int(10, app.config.USERNAME)
        amount -= num
        app.config.update(dict(
            AMOUNT=amount))
        transfer = struct.pack(
            '=20sc2i', app.config['USERNAME'], b'a', num, id, app.config['USERNAME'], app.config['PASSWORD'], app.config['AMOUNT'], )
        return redirect(url_for('show_entries'))
    return render_template('login.html', error=error)
# 存钱


@app.route('/login', methods=['GET', 'POST'])
def login():
    error = None
    if request.method == 'POST':
        id = int(10, request.form['username'])
        transfer = struct.pack(
            '=20sc2i', request.form['username'], b'c', 0, id, )
        fd = os.open('%s.fifo' % './instance/fifo/' +
                     request.form['username'], os.O_RDONLY)

        re = os.read(fd, 135)
        status = struct.unpack('=2ci20s105si', re)
        if status[1] == 0:
            error = 'Login Error'
        elif not(status[4] == request.form['password']):
            error = 'Invalid password'
        else:
            session['logged_in'] = True
            app.config.update(dict(
                USERNAME=request.form['username'],
                PASSWORD=request.form['password'],
                AMOUNT=status[3][2]))
            flash('You were logged in')
            return redirect(url_for('show_entries'))
    return render_template('login.html', error=error)

# 登出页面


@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    flash('You were logged out')
    return redirect(url_for('show_entries'))


if __name__ == '__main__':
    app.run()
