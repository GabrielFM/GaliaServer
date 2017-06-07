# all the imports
import os
import sqlite3
from flask import Flask, request, session, g, redirect, url_for, abort, render_template, flash
import time

from gpio_96boards import GPIO




app = Flask(__name__) # create the application instance :)
app.config.from_object(__name__) # load config from this file , flaskr.py


# Load default config and override config from an environment variable
app.config.update(dict(
    DATABASE=os.path.join(app.root_path, 'galia.db'),
    SECRET_KEY='development key',
    USERNAME='admin',
    PASSWORD='default'
))
app.config.from_envvar('GALIA_SETTINGS', silent=True)

@app.route('/casa')
def __show_entries():
    GPIO_A = GPIO.gpio_id('GPIO_A')
    pins = ((GPIO_A, 'out'),)
    with GPIO(pins) as gpio:
        for i in range(5):
            gpio.digital_write(GPIO_A, GPIO.HIGH)
            time.sleep(i)
            gpio.digital_write(GPIO_A, GPIO.LOW)
            time.sleep(1)
    return render_template('home.html', valor1=1, valor2=0)


@app.route('/')
def show_entries():
    valor1 = 500
    valor2 = 600
    return render_template('home.html', valor1=valor1, valor2=valor2)

def connect_db():
    """Connects to the specific database."""
    rv = sqlite3.connect(app.config['DATABASE'])
    rv.row_factory = sqlite3.Row
    return rv

def get_db():
    """Opens a new database connection if there is none yet for the
    current application context.
    """
    if not hasattr(g, 'sqlite_db'):
        g.sqlite_db = connect_db()
    return g.sqlite_db

@app.teardown_appcontext
def close_db(error):
    """Closes the database again at the end of the request."""
    if hasattr(g, 'sqlite_db'):
        g.sqlite_db.close()

def init_db():
    db = get_db()
    with app.open_resource('schema.sql', mode='r') as f:
        db.cursor().executescript(f.read())
    db.commit()

@app.cli.command('initdb')
def initdb_command():
    """Initializes the database."""
    init_db()
    print('Initialized the database.')
