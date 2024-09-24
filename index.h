const char *HTML_CONTENT = R"=====(
<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Spy RC Car Control Panel</title>
    <style>
        body {
            font-family: 'Courier New', monospace;
            background-color: #0a0a0a;
            color: #00ff00;
            margin: 0;
            padding: 0;
            display: flex;
            flex-direction: column;
            height: 100vh;
            width: 388px;
        }
        #stream-container {
            width: 100%;
            height: 300px;
            overflow: hidden;
            position: relative;
        }
        #stream {
            width: 100%;
            height: 100%;
            object-fit: cover;
        }
        #container {
            display: grid;
            grid-template-columns: repeat(3, 1fr);
            grid-template-rows: repeat(3, 1fr);
            gap: 10px;
            padding: 10px;
        }
        .button {
            background-color: #1a1a1a;
            border: 1px solid #00ff00;
            color: #00ff00;
            padding: 15px;
            text-align: center;
            text-decoration: none;
            display: flex;
            align-items: center;
            justify-content: center;
            font-size: 16px;
            cursor: pointer;
            transition: all 0.3s ease;
        }
        .button:active {
            background-color: #00ff00;
            color: #1a1a1a;
        }
        #up { grid-area: 1 / 2 / 3 / 3; }
        #left { grid-area: 1 / 1 / 3 / 2; }
        #stop { grid-area: 2 / 2 / 3 / 3; }
        #right { grid-area: 1 / 3 / 3 / 4; }
        #down { grid-area: 3 / 2 / 4 / 3; }
        .control-panel {
            background-color: #1a1a1a;
            border: 1px solid #00ff00;
            padding: 8px;
            margin: 10px;
        }
        #speed_control, #servo-control {
            display: flex;
            justify-content: space-between;
            align-items: center;
            margin: 10px 0;
        }
        .slider {
            -webkit-appearance: none;
            width: 70%;
            height: 5px;
            background: #00ff00;
            outline: none;
            opacity: 0.7;
            transition: opacity .2s;
        }
        .slider::-webkit-slider-thumb {
            -webkit-appearance: none;
            appearance: none;
            width: 15px;
            height: 15px;
            background: #00ff00;
            cursor: pointer;
        }
        .button-container {
            display: flex;
            justify-content: space-around;
            margin: 10px;
        }
        .button-container button {
            background-color: #1a1a1a;
            border: 1px solid #00ff00;
            color: #00ff00;
            padding: 5px 10px;
            font-size: 12px;
        }
        .footer {
            text-align: center;
            font-size: 12px;
            padding: 10px;
            background-color: #1a1a1a;
            border-top: 1px solid #00ff00;
        }
		/* Стили для LED кнопок */
.led-button {
    padding: 3px 10px;
    font-size: 14px;
    background-color: #1a1a1a;
    color: #00ff00;
    border: 1px solid #00ff00;
    border-radius: 3px;
    cursor: pointer;
    transition: all 0.3s ease;
    margin: 5px;
    text-shadow: 0 0 5px #00ff00;
    box-shadow: 0 0 5px #00ff00;
}

.led-button:hover {
    background-color: #00ff00;
    color: #000000;
}

/* Стили для кнопок серво */
.servo-button {
    padding: 5px 10px;
    font-size: 16px;
    background-color: #1a1a1a;
    color: #00ffff;
    border: 1px solid #00ffff;
    border-radius: 3px;
    cursor: pointer;
    transition: all 0.3s ease;
    margin: 0 5px;
    text-shadow: 0 0 5px #00ffff;
    box-shadow: 0 0 5px #00ffff;
}

.servo-button:hover {
    background-color: #00ffff;
    color: #000000;
}

/* Стили для слайдеров */
input[type="range"] {
    -webkit-appearance: none;
    width: 190px;
    height: 10px;
    background: #1a1a1a;
    outline: none;
    border: 1px solid #00ff00;
    border-radius: 5px;
    box-shadow: 0 0 5px #00ff00;
}

input[type="range"]::-webkit-slider-thumb {
    -webkit-appearance: none;
    appearance: none;
    width: 20px;
    height: 20px;
    background: #00ff00;
    cursor: pointer;
    border-radius: 50%;
    box-shadow: 0 0 10px #00ff00;
}

input[type="range"]::-moz-range-thumb {
    width: 20px;
    height: 20px;
    background: #00ff00;
    cursor: pointer;
    border-radius: 50%;
    box-shadow: 0 0 10px #00ff00;
}

/* Специфичные стили для LED слайдера */
#led-slider {
    border-color: #ff00ff;
    box-shadow: 0 0 5px #ff00ff;
}

#led-slider::-webkit-slider-thumb {
    background: #ff00ff;
    box-shadow: 0 0 10px #ff00ff;
}

#led-slider::-moz-range-thumb {
    background: #ff00ff;
    box-shadow: 0 0 10px #ff00ff;
}

/* Контейнер для группировки элементов управления серво */
.servo-control {
    display: flex;
    align-items: center;
    justify-content: center;
    margin: 10px 0;
}
/* Стиль для кнопки Connect */
#wc_conn {
    padding: 1px 8px;
    font-size: 18px;
    background-color: #1a1a1a;
    color: #ff0000;
    border: 2px solid #ff0000;
    border-radius: 5px;
    cursor: pointer;
    transition: all 0.3s ease;
    margin: 10px;
    text-transform: uppercase;
    font-weight: bold;
    letter-spacing: 2px;
    text-shadow: 0 0 10px #ff0000;
    box-shadow: 0 0 15px #ff0000;
    position: relative;
    overflow: hidden;
}

#wc_conn::before {
    content: '';
    position: absolute;
    top: -50%;
    left: -50%;
    width: 200%;
    height: 200%;
    background: rgba(255, 0, 0, 0.1);
    transform: rotate(45deg);
    transition: all 0.3s ease;
    z-index: -1;
}

#wc_conn:hover {
    background-color: #ff0000;
    color: #000000;
}

#wc_conn:hover::before {
    top: -100%;
    left: -100%;
}

/* Анимация пульсации для кнопки Connect */
@keyframes pulse {
    0% {
        box-shadow: 0 0 15px #ff0000;
    }
    50% {
        box-shadow: 0 0 30px #ff0000, 0 0 40px #ff0000;
    }
    100% {
        box-shadow: 0 0 15px #ff0000;
    }
}

#wc_conn {
    animation: pulse 2s infinite;
}
    </style>
</head>
<body>
    <div id="stream-container">
        <img src="http://192.168.3.100:81/stream" id="stream" crossorigin="">
    </div>

    <div id="container">
        <div id="up" class="button">^</div>
        <div id="left" class="button"><</div>
        <!--<div id="stop" class="button">¦</div>-->
        <div id="right" class="button">></div>
        <div id="down" class="button">v</div>
    </div>

    <div class="control-panel">
        <button class="led-button" id="led1_button" onclick="toggleLED(1)">LED1 (D4): ON</button>
        <button class="led-button" id="led2_button" onclick="toggleLED(2)">LED2 (D0): ON</button>
        <div id="speed_control">
            <label for="speed">Motor Speed: </label>
            <input type="range" id="speed" name="speed" min="1" max="255" value="45" onchange="updateSpeed(this.value)">
            <span id="speed_value">255</span>
        </div>
        <div id="servo-control">
            <button class="servo-button" onclick="moveServo('left')"><</button>
            <input type="range" id="servo-slider" min="0" max="180" value="90" oninput="updateServoPosition(this.value)">
            <button class="servo-button" onclick="moveServo('right')">></button>
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
        WebSocket: <span id="ws_state">CLOSED</span>
        <button id="wc_conn" onclick="wc_onclick();" >Connect</button>
    </div>

    <div class="footer">
        © 2024 Denjik AI. All rights reserved.
        <a href="/about.html" style="color: #00ff00;">About</a>
        <a href="/play.html" style="color: #556546;">Old</a>
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
