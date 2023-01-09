from flask import Flask, render_template, Response, request
import json
import serial


app = Flask(__name__)

s = serial.Serial(port="COM5", baudrate=9600, timeout = 2, bytesize=8, stopbits=serial.STOPBITS_ONE)


@app.route('/')
def hello():
    return render_template('index.html')


@app.route('/schedule', methods=["GET", "POST"])
def schedule():
    if request.method == "POST":
        global s

        time1 = request.form.get("time1")
        time2 = request.form.get("time2")
        time3 = request.form.get("time3")

        to_write = f"{time1} {time2} {time3}"
        s.write(to_write.encode('utf-8'))
    
        return render_template('schedule.html', time1=time1, time2=time2, time3=time3) # must be in templates folder


if __name__ == "__main__":
    app.run("0.0.0.0", port=8040)


s.close()
