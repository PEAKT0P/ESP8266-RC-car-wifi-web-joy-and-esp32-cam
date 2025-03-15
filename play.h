const char *PLAY_HTML_CONTENT = R"=====(
<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <title>Denjik AI RC Car Control</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 0;
            padding: 1px;
            text-align: center;
            transition: background-color 0.3s, color 0.3s;
        }
        body.dark-theme {
            background-color: #222;
            color: #fff;
        }
        body.light-theme {
            background-color: #f0f0f0;
            color: #333;
        }
        h1 {
            margin-bottom: 10px;
        }
        #container {
            width: 300px;
            height: 300px;
            margin: 0 auto 20px;
            position: relative;
        }
        .button {
            position: absolute;
            border: none;
            border-radius: 10px;
            cursor: pointer;
            transition: all 0.3s ease;
        }
        .button:active {
            transform: scale(0.95);
            box-shadow: 0 2px 5px rgba(0,0,0,0.2);
        }
        #up { width: 100px; height: 100px; top: 0; left: 100px; }
        #down { width: 100px; height: 100px; bottom: 0; left: 100px; }
        #left { width: 100px; height: 100px; top: 100px; left: 0; }
        #right { width: 100px; height: 100px; top: 100px; right: 0; }
        #stop { width: 50px; height: 50px; top: 125px; left: 125px; }
        
        .dark-theme #up { background-color: #2ecc71; }
        .dark-theme #down { background-color: #e74c3c; }
        .dark-theme #left { background-color: #f39c12; }
        .dark-theme #right { background-color: #3498db; }
        .dark-theme #stop { background-color: #7f8c8d; }
        
        .light-theme #up { background-color: #4CAF50; }
        .light-theme #down { background-color: #f44336; }
        .light-theme #left { background-color: #FF9800; }
        .light-theme #right { background-color: #2196F3; }
        .light-theme #stop { background-color: #9E9E9E; }
        
        .control-panel {
            border-radius: 10px;
            padding: 20px;
            margin-bottom: 20px;
            box-shadow: 0 2px 10px rgba(0,0,0,0.1);
            transition: background-color 0.3s;
        }
#stream-container {
    border: 1px solid #ccc;
    padding: 1px;
    width: 388px;
    border-radius: 1px;
    background-color: #000;
    margin-bottom: 15px;
    margin-left: auto;
    margin-right: auto;
    position: relative; /* Добавлено для позиционирования */
    touch-action: none; /* Отключаем стандартное поведение для сенсорных экранов */
}

.resizable {
    resize: both; /* Позволяет изменять размер контейнера */
    overflow: auto; /* Добавляем прокрутку при необходимости */
}
        .dark-theme .control-panel {
            background-color: #333;
        }
        .light-theme .control-panel {
            background-color: white;
        }
        button {
            border: none;
            color: white;
            padding: 10px 20px;
            text-align: center;
            text-decoration: none;
            display: inline-block;
            font-size: 16px;
            margin: 4px 2px;
            cursor: pointer;
            border-radius: 5px;
            transition: background-color 0.3s;
        }
        .dark-theme button {
            background-color: #2ecc71;
        }
        .light-theme button {
            background-color: #4CAF50;
        }
        input[type="range"] {
            width: 200px;
        }
        #ws_state {
            font-weight: bold;
        }
        .footer {
            margin-top: 20px;
            transition: color 0.3s;
            font-size: 10px;
        }
        .dark-theme .footer {
            color: #bbb;
        }
        .light-theme .footer {
            color: #666;
        }
        #theme-toggle {
            position: absolute;
            top: 10px;
            right: 10px;
            background-color: transparent;
            border: none;
            cursor: pointer;
            font-size: 24px;
        }
        #servo-control {
            margin-top: 20px;
            display: flex;
            justify-content: center;
            align-items: center;
        }
        #servo-slider {
            width: 200px;
            margin: 0 10px;
        }
        .servo-button {
            font-size: 24px;
            padding: 5px 10px;
            background-color: #3498db;
            color: white;
            border: none;
            border-radius: 5px;
            cursor: pointer;
        }
        .dark-theme .servo-button {
            background-color: #2980b9;
        }
        .light-theme .servo-button {
            background-color: #3498db;
        }
		#led-control {
    width: 300px;
    margin: 20px auto;
    padding: 20px;
    border-radius: 10px;
    box-shadow: 0 2px 10px rgba(0,0,0,0.1);
    transition: background-color 0.3s;
}
.dark-theme #led-control {
    background-color: #333;
    color: #fff;
}
.light-theme #led-control {
    background-color: white;
    color: #333;
}
#led-control h3 {
    margin-bottom: 15px;
}
#led-slider {
    width: 200px;
    margin: 10px 0;
}
#led-value {
    font-weight: bold;
    margin-left: 10px;
}
.button-container {
    display: flex;
    gap: 5px;
    margin-top: 10px;
    justify-content: center;
    flex-wrap: wrap; /* Добавлено для переноса кнопок */
}
.button-container button {
    padding: 5px 10px;
    border: none;
    border-radius: 5px;
    color: white;
    font-weight: bold;
    cursor: pointer;
}

.btn-off { background-color: #333 !important; }
.btn-30 { background-color: #66c2ff !important; }
.btn-60 { background-color: #3399ff !important; }
.btn-90 { background-color: #0080ff !important; }
.btn-110 { background-color: #0066cc !important; }
.btn-145 { background-color: #004c99 !important; }
.btn-255 { background-color: #ff3333 !important; }

    </style>
</head>
<body class="dark-theme">
    <button id="theme-toggle" onclick="toggleTheme()">☀️</button>
    <!--<h1>Denjik AI RC Car Control</h1>-->
<div id="stream-container" class="draggable resizable">
    <img style="width: 390px; height:300px;" id="stream" src="http://192.168.3.100:81/stream" crossorigin>
</div>
    <div id="container">
        <div id="up" class="button"></div>
        <div id="down" class="button"></div>
        <div id="left" class="button"></div>
        <div id="right" class="button"></div>
        <div id="stop" class="button"></div>
    </div>
    <div class="control-panel">
        <button id="led1_button" onclick="toggleLED(1)">LED1 (D4): ON</button>
        <button id="led2_button" onclick="toggleLED(2)">LED2 (D0): ON</button>
        <div id="speed_control">
            <label for="speed">Motor Speed: </label>
            <input type="range" id="speed" name="speed" min="1" max="255" value="255" onchange="updateSpeed(this.value)">
            <span id="speed_value">255</span>
        </div>
        <div id="servo-control">
            <button class="servo-button" onclick="moveServo('left')">←</button>
            <input type="range" id="servo-slider" min="0" max="180" value="90" oninput="updateServoPosition(this.value)">
            <button class="servo-button" onclick="moveServo('right')">→</button>
        </div>
        <p>Servo Position: <span id="servo-position">90</span>°</p>
			<!--<div id="led-control">-->
<label for="led-slider">LED Control</label>
            <input type="range" id="led-slider" min="0" max="145" value="0">
            <span id="led-value">0</span>
        </div>
        <div class="button-container">
            <button class="btn-off" data-value="0">OFF</button>
            <button class="btn-30" data-value="1">1%</button>
            <button class="btn-60" data-value="5">5%</button>
            <button class="btn-90" data-value="15">15%</button>
            <button class="btn-110" data-value="50">50%</button>
            <button class="btn-145" data-value="145">145%</button>
            <button class="btn-255" data-value="255">255</button>
        </div>
    </div>
</div>

    <script>
    (function() {
        const slider = document.getElementById('led-slider');
        const valueDisplay = document.getElementById('led-value');
        const buttons = document.querySelectorAll('.button-container button');
        const espHost = 'http://192.168.3.100'; // IP-адрес вашего ESP32 с камерой

        function updateLED(value) {
            valueDisplay.textContent = value;
            slider.value = value;
            fetch(`${espHost}/control?var=led_intensity&val=${value}`, {
                method: 'GET',
                mode: 'cors'
            }).catch(error => console.error('Error updating LED:', error));
        }

        slider.oninput = function() {
            updateLED(this.value);
        };

        buttons.forEach(button => {
            button.addEventListener('click', function() {
                const value = this.getAttribute('data-value');
                updateLED(value);
            });
        });
    })();
    </script>
    <div class="control-panel">
        <p>WebSocket: <span id="ws_state">CLOSED</span></p>
        <button id="wc_conn" onclick="wc_onclick();">Connect</button>
    </div>
    <div class="footer">
        <p>© 2025 <span class="highlight">Denjik</span> AI. All rights reserved. <a href="/about.html">About</a></p>
        &copy; 2024 Denjik AI. All rights reserved. <a style="color: #556546; " href="/">JOY</a><a style="color: #556546; " href="/system.html">System</a>
    </div>
    <script>
    var CMD_STOP = 0, CMD_FORWARD = 1, CMD_BACKWARD = 2, CMD_LEFT = 4, CMD_RIGHT = 8, CMD_LED1 = 16, CMD_LED2 = 32, CMD_SERVO_MOVE = 64, CMD_SERVO_LEFT = 128, CMD_SERVO_RIGHT = 256;
    var ws = null;
    var led1_state = true, led2_state = true;

    var pingInterval;

    function init() {
        document.querySelectorAll('.button').forEach(btn => {
            btn.addEventListener('touchstart', buttonPress);
            btn.addEventListener('touchend', buttonRelease);
            btn.addEventListener('mousedown', buttonPress);
            btn.addEventListener('mouseup', buttonRelease);
            btn.addEventListener('mouseleave', buttonRelease);
        });
    }

    function buttonPress(event) {
        event.preventDefault();
        let command;
        switch(event.target.id) {
            case 'up': command = CMD_FORWARD; break;
            case 'down': command = CMD_BACKWARD; break;
            case 'left': command = CMD_LEFT; break;
            case 'right': command = CMD_RIGHT; break;
            case 'stop': command = CMD_STOP; break;
        }
        send_command(command);
        event.target.style.opacity = '0.7';
    }

    function buttonRelease(event) {
        event.preventDefault();
        send_command(CMD_STOP);
        event.target.style.opacity = '1';
    }

    function ws_onopen() {
        document.getElementById("ws_state").innerHTML = "OPEN";
        document.getElementById("wc_conn").innerHTML = "Disconnect";
        pingInterval = setInterval(sendPing, 2000);
    }

    function ws_onclose() {
        document.getElementById("ws_state").innerHTML = "CLOSED";
        document.getElementById("wc_conn").innerHTML = "Connect";
        ws = null;
        clearInterval(pingInterval);
    }

    function wc_onclick() {
        if(ws == null) {
            ws = new WebSocket("ws://" + window.location.host + ":81");
            document.getElementById("ws_state").innerHTML = "CONNECTING";
            ws.onopen = ws_onopen;
            ws.onclose = ws_onclose;
        } else {
            ws.close();
        }
    }
    function sendPing() {
        if(ws != null && ws.readyState == 1) {
            ws.send("PING");
        }
    }

    function send_command(cmd) {
        if(ws != null && ws.readyState == 1) {
            ws.send(cmd + "\r\n");
        }
    }

    function toggleLED(led_num) {
        var command = led_num == 1 ? CMD_LED1 : CMD_LED2;
        if (led_num == 1) {
            led1_state = !led1_state;
            document.getElementById("led1_button").innerHTML = "LED1 (D4): " + (led1_state ? "ON" : "OFF");
        } else {
            led2_state = !led2_state;
            document.getElementById("led2_button").innerHTML = "LED2 (D0): " + (led2_state ? "ON" : "OFF");
        }
        send_command(command);
    }

    function updateSpeed(speed) {
        document.getElementById('speed_value').innerText = speed;
        if(ws != null && ws.readyState == 1) {
            ws.send("SPEED:" + speed);
        }
    }

    function updateServoPosition(position) {
        document.getElementById('servo-position').innerText = position;
        if(ws != null && ws.readyState == 1) {
            ws.send("SERVO:" + position);
        }
    }

    function moveServo(direction) {
        if(ws != null && ws.readyState == 1) {
            if(direction === 'left') {
                ws.send(CMD_SERVO_LEFT);
            } else if(direction === 'right') {
                ws.send(CMD_SERVO_RIGHT);
            }
        }
    }

    function toggleTheme() {
        const body = document.body;
        const themeToggle = document.getElementById('theme-toggle');
        if (body.classList.contains('dark-theme')) {
            body.classList.remove('dark-theme');
            body.classList.add('light-theme');
            themeToggle.textContent = '🌙';
        } else {
            body.classList.remove('light-theme');
            body.classList.add('dark-theme');
            themeToggle.textContent = '☀️';
        }
    }

    window.onload = init;
    </script>
    <script>
    document.addEventListener('DOMContentLoaded', function (event) {
        const qualitySlider = document.getElementById('quality');
        if (qualitySlider) {
            qualitySlider.value = 60; // Установить значение на 60
            qualitySlider.dispatchEvent(new Event('change')); // Триггерим событие изменения для применения
        }
    });
	
	
	// stream
	
	const streamContainer = document.getElementById('stream-container');

let isDragging = false;
let startX, startY, initialX, initialY;

streamContainer.addEventListener('touchstart', (e) => {
    isDragging = true;
    startX = e.touches[0].clientX;
    startY = e.touches[0].clientY;
    initialX = streamContainer.offsetLeft;
    initialY = streamContainer.offsetTop;
});

document.addEventListener('touchmove', (e) => {
    if (isDragging) {
        const dx = e.touches[0].clientX - startX;
        const dy = e.touches[0].clientY - startY;
        streamContainer.style.left = `${initialX + dx}px`;
        streamContainer.style.top = `${initialY + dy}px`;
    }
});

document.addEventListener('touchend', () => {
    isDragging = false;
});
	
</script>

</body>
</html>
)=====";
