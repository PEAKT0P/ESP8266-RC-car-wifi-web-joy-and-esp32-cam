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
    width: 388px;
    height: 300px;
    position: relative;
    overflow: hidden;
  }
  #stream {
    width: 100%;
    height: 100%;
    object-fit: cover;
  }
  .overlay {
    position: absolute;
    top: 0;
    left: 0;
    width: 100%;
    height: 100%;
    pointer-events: none;
  }
  .neon-text {
    position: absolute;
    font-family: Arial, sans-serif;
    font-weight: bold;
    text-shadow: 0 0 5px currentColor, 0 0 10px currentColor, 0 0 15px currentColor;
  }
  .top-left {
    top: 10px;
    left: 10px;
    color: #0ff;
    font-size: 11px;
  }
  .bottom-left {
    bottom: 10px;
    left: 10px;
    display: flex;
    align-items: center;
  }
  .rec-text {
    color: #f0f;
    font-size: 14px;
    margin-right: 5px;
  }
  .rec-indicator {
    width: 10px;
    height: 10px;
    border-radius: 50%;
    background-color: #0f0;
    box-shadow: 0 0 5px #0f0, 0 0 10px #0f0;
    animation: blink 1s infinite;
  }
  .bottom-right {
    bottom: 10px;
    right: 10px;
    color: #00f;
    font-size: 10px;
  }
  .crosshair {
    position: absolute;
    top: 50%;
    left: 50%;
    transform: translate(-50%, -50%);
    width: 40px;
    height: 40px;
  }
  .crosshair::before,
  .crosshair::after {
    content: '';
    position: absolute;
    background-color: #0f0;
    box-shadow: 0 0 5px #0f0, 0 0 10px #0f0;
  }
  .crosshair::before {
    top: 50%;
    left: 0;
    right: 0;
    height: 0.5px;
    transform: translateY(-50%);
  }
  .crosshair::after {
    left: 50%;
    top: 0;
    bottom: 0;
    width: 0.5px;
    transform: translateX(-50%);
  }
  @keyframes blink {
    0%, 100% { opacity: 1; }
    50% { opacity: 0.5; }
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
            font-size: 10px;
            padding: 10px;
            background-color: #1a1a1a;
            border-top: 1px solid #00ff00;
        }
.led-button {
    padding: 3px 10px;
    font-size: 14px;
    background-color: #1a1a1a;
    color: #00b6ff;
    border: 1px solid #2400ff;
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
    color: #00ad0f;
    border: 1px solid #00ff00;
    border-radius: 3px;
    cursor: pointer;
    transition: all 0.3s ease;
    margin: 0 5px;
    text-shadow: 0 0 5px #00ffff;
    box-shadow: 0 0 5px #00ffff;
}

.servo-button:hover {
    background-color: #005c81;
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
    border-color: #ffe400;
    box-shadow: 0 0 5px #00ffac;
}

#led-slider::-webkit-slider-thumb {
    background: #024f4f;
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
/* ADD TO THE STYLE SECTION: */
#joystick-container {
    display: flex;
    justify-content: center;
    align-items: center;
    width: 100%;
    height: 200px;
    margin: 20px 0;
}

#joystick-base {
    position: relative;
    width: 180px;
    height: 180px;
    background-color: #1a1a1a;
    border: 2px solid #00ff00;
    border-radius: 50%;
    box-shadow: 0 0 10px #00ff00;
}

#joystick-thumb {
    position: absolute;
    width: 70px;
    height: 70px;
    background-color: #333;
    border: 2px solid #00ff00;
    border-radius: 50%;
    top: 50%;
    left: 50%;
    transform: translate(-50%, -50%);
    cursor: pointer;
    box-shadow: inset 0 0 10px #00ff00, 0 0 15px #00ff00;
}
/* In index.h, add these styles to the <style> section */

/* Mobile optimization for vertical screens */
@media screen and (max-width: 480px) {
    body {
        width: 100%;
        max-width: 393px;
        margin: 0 auto;
        padding: 0;
        font-size: 14px;
    }
    
    #stream-container {
        width: 100%;
        height: 250px; /* Smaller height on mobile */
    }
    
    #joystick-container {
        height: 170px; /* Smaller joystick area */
        margin: 10px 0;
    }
    
    #joystick-base {
        width: 160px;
        height: 160px;
    }
    
    #joystick-thumb {
        width: 60px;
        height: 60px;
    }
    
    .control-panel {
        padding: 5px;
        margin: 5px;
    }
    
    .button {
        padding: 10px;
        font-size: 14px;
    }
    
    .servo-button, .led-button {
        padding: 3px 8px;
        font-size: 12px;
        margin: 3px;
    }
    
    input[type="range"] {
        width: 150px;
    }
    
    .button-container {
        flex-wrap: wrap;
    }
    
    .button-container button {
        margin: 3px;
        padding: 3px 6px;
        font-size: 10px;
    }
    
    .footer {
        padding: 5px;
        font-size: 9px;
    }
}

/* Fix joystick touch behavior for better response */
#joystick-base {
    touch-action: none;
}

/* Make controls more finger-friendly */
button, input[type="range"] {
    touch-action: manipulation;
}

    </style>
</head>
<body>
<div id="stream-container">
  <img src="http://192.168.3.100:81/stream" id="stream" crossorigin="">
  <div class="overlay">
    <div class="neon-text top-left">RC Car</div>
    <div class="neon-text bottom-left">
      <span class="rec-text">REC</span>
      <div class="rec-indicator"></div>
    </div>
    <div class="neon-text bottom-right">CONNECT</div>
    <div class="crosshair"></div>
  </div>
</div>

   <!-- WITH THIS NEW JOYSTICK CONTAINER: -->
    <div class="control-panel">
        <div id="joystick-container">
            <div id="joystick-base">
                <div id="joystick-thumb"></div>
            </div>
        </div>
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
        © 2025 Denjik AI. All rights reserved.
        <a href="/about.html" style="color: #00ff00;">About</a>
        <!--<a href="/play.html" style="color: #556546;">Old</a>-->
		<a href="/system.html" style="color: #556546">System</a>
    </div>

<script>
    var CMD_STOP = 0, CMD_FORWARD = 1, CMD_BACKWARD = 2, CMD_LEFT = 4, CMD_RIGHT = 8, CMD_LED1 = 16, CMD_LED2 = 32, CMD_SERVO_MOVE = 64, CMD_SERVO_LEFT = 128, CMD_SERVO_RIGHT = 256;
    var ws = null;
    var led1_state = true, led2_state = true;

    pingInterval = setInterval(sendPing, 3000); // Reduce ping frequency to every 3 seconds

    // WITH THIS NEW JOYSTICK CODE:
// In index.h, replace the existing joystick handling code with:
var CMD_FORWARD_LEFT = 512, CMD_FORWARD_RIGHT = 1024, CMD_BACKWARD_LEFT = 2048, CMD_BACKWARD_RIGHT = 4096;

function init() {
    const joystickThumb = document.getElementById('joystick-thumb');
    const joystickBase = document.getElementById('joystick-base');
    
    let isDragging = false;
    let currentCommand = CMD_STOP;
    let lastCommandSent = 0;
    const commandThrottleMs = 50; // Send commands every 50ms at most
    
    // Get joystick dimensions and position
    const baseRect = joystickBase.getBoundingClientRect();
    const maxDistance = baseRect.width / 2 - joystickThumb.offsetWidth / 2;
    
    function getJoystickCenter() {
        // Recalculate center each time to handle potential layout shifts
        const rect = joystickBase.getBoundingClientRect();
        return {
            x: rect.left + rect.width / 2,
            y: rect.top + rect.height / 2
        };
    }
    
    function handleJoystickMove(clientX, clientY) {
        if (!isDragging) return;
        
        const center = getJoystickCenter();
        
        // Calculate distance from center
        let deltaX = clientX - center.x;
        let deltaY = clientY - center.y;
        
        // Calculate distance from center
        const distance = Math.sqrt(deltaX * deltaX + deltaY * deltaY);
        
        // Normalize if distance is greater than max
        if (distance > maxDistance) {
            deltaX = deltaX * maxDistance / distance;
            deltaY = deltaY * maxDistance / distance;
        }
        
        // Update joystick thumb position
        joystickThumb.style.transform = `translate(calc(-50% + ${deltaX}px), calc(-50% + ${deltaY}px))`;
        
        // Deadzone handling
        const deadzone = 15; // Dead zone radius in pixels
        
        const now = Date.now();
        if (now - lastCommandSent < commandThrottleMs) {
            return; // Throttle command rate
        }
        
        // Only send commands if outside the dead zone
        if (distance > deadzone) {
            // Calculate X and Y components for direction
            const normX = deltaX / maxDistance; // -1 to 1
            const normY = deltaY / maxDistance; // -1 to 1
            
            // Determine command based on normalized X and Y
            let newCommand = CMD_STOP;
            
            // Determine forward/backward component
            if (normY < -0.25) {
                newCommand = CMD_FORWARD;
            } else if (normY > 0.25) {
                newCommand = CMD_BACKWARD;
            }
            
            // Add turning component
            if (normX < -0.25) {
                if (newCommand === CMD_FORWARD) {
                    newCommand = CMD_FORWARD_LEFT;
                } else if (newCommand === CMD_BACKWARD) {
                    newCommand = CMD_BACKWARD_LEFT;
                } else {
                    newCommand = CMD_LEFT;
                }
            } else if (normX > 0.3) {
                if (newCommand === CMD_FORWARD) {
                    newCommand = CMD_FORWARD_RIGHT;
                } else if (newCommand === CMD_BACKWARD) {
                    newCommand = CMD_BACKWARD_RIGHT;
                } else {
                    newCommand = CMD_RIGHT;
                }
            }
            
            // Only send if command changed
            if (newCommand !== currentCommand) {
                send_command(newCommand);
                currentCommand = newCommand;
                lastCommandSent = now;
            }
        } else if (currentCommand !== CMD_STOP) {
            send_command(CMD_STOP);
            currentCommand = CMD_STOP;
            lastCommandSent = now;
        }
    }
    
    // Touch events for mobile (prioritize these for mobile-first approach)
    joystickBase.addEventListener('touchstart', (e) => {
        isDragging = true;
        e.preventDefault();
        const touch = e.touches[0];
        handleJoystickMove(touch.clientX, touch.clientY);
    }, { passive: false });

    document.addEventListener('touchmove', (e) => {
        if (isDragging) {
            e.preventDefault();
            const touch = e.touches[0];
            handleJoystickMove(touch.clientX, touch.clientY);
        }
    }, { passive: false });

    document.addEventListener('touchend', () => {
        isDragging = false;
        joystickThumb.style.transform = 'translate(-50%, -50%)';
        send_command(CMD_STOP);
        currentCommand = CMD_STOP;
    });
    
    // Mouse events as fallback
    joystickBase.addEventListener('mousedown', (e) => {
        isDragging = true;
        handleJoystickMove(e.clientX, e.clientY);
    });
    
    document.addEventListener('mousemove', (e) => {
        handleJoystickMove(e.clientX, e.clientY);
    });
    
    document.addEventListener('mouseup', () => {
        isDragging = false;
        joystickThumb.style.transform = 'translate(-50%, -50%)';
        send_command(CMD_STOP);
        currentCommand = CMD_STOP;
    });
    
    // Initialize websocket connection automatically
    if (ws == null) {
        ws = new WebSocket("ws://" + window.location.host + ":81");
        document.getElementById("ws_state").innerHTML = "CONNECTING";
        ws.onopen = ws_onopen;
        ws.onclose = ws_onclose;
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
	/*
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
*/
//antitouch
    (function() {
    // Запрет выделения текста
    document.body.style.webkitUserSelect = 'none';
    document.body.style.userSelect = 'none';

    // Запрет контекстного меню
    document.addEventListener('contextmenu', function(e) {
        e.preventDefault();
    }, false);

    // Запрет touch контекстного меню (для мобильных устройств)
    document.addEventListener('touchstart', function(e) {
        if (e.touches.length > 1) {
            e.preventDefault();
        }
    }, { passive: false });

    // Запрет zoom через жесты (для мобильных устройств)
    document.addEventListener('gesturestart', function(e) {
        e.preventDefault();
    }, false);
})();
</script>
</body>
</html>
)=====";
