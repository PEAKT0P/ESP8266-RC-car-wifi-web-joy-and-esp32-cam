const char *SYSTEMSTAT_HTML_CONTENT = R"=====(
<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
    <title>Системная информация</title>
    <style>
        body {
            font-family: "Courier New", Courier, monospace;
            background-color: #000; /* Изменяем цвет фона */
            color: #00ff00; /* Изменяем цвет текста */
            margin: 0;
            //padding: 10px;
            overflow: auto;
            width: 388px;
            height: 10%;
        }
        header {
            //background-color: #990000; /* Изменяем цвет фона */
            color: #ffffff; /* Изменяем цвет текста */
            padding: 10px;
            text-align: center;
            border-bottom: 2px solid #00ff00; /* Изменяем цвет границы */
        }
        h1 {
            font-size: 1.5em;
            margin: 0;
            color: #ffff00; /* Изменяем цвет текста */
        }
        section {
            padding: 10px;
            //background-color: #330099; /* Изменяем цвет фона */
        }
        h2 {
            font-size: 1.3em;
            margin-bottom: 10px;
            color: #00ff00; /* Изменяем цвет текста */
            border-bottom: 1px solid #00ffff; /* Изменяем цвет границы */
        }
        p {
            font-size: 1.1em;
            line-height: 1.5em;
            margin: 10px 0;
            color: #0000ff; /* Изменяем цвет текста */
        }
        .highlight {
            color: #ffff00; /* Изменяем цвет текста */
        }
        footer {
		    position: fixed;
			bottom: 0;
			width: 100%;
            //position: absolute;
            //bottom: 10px;
            width: 100%;
            font-size: 0.8em;
            text-align: center;
            color: #0000ff; /* Изменяем цвет текста */
        }
        a {
            color: #00ffff; /* Изменяем цвет текста */
            text-decoration: none;
        }
        a:hover {
            color: #ffffff; /* Изменяем цвет текста */
        }
    </style>
</head>
<body>
    <header>
        <h1>Системная информация RC Машинки</h1>
    </header>

    <section>
        <h2>О системе</h2>
        <p>
            Эта RC машина оснащена умными датчиками и управляется с помощью мощного веб-интерфейса.
        </p>

        <h2>Системная информация</h2>
        <table id="system_info">
            <tr>
                <th>Параметр</th>
                <th>Значение</th>
            </tr>
            <tr>
                <td>Загрузка CPU</td>
                <td><span id="cpu_load" style="color: #00ff00">0%</span></td>
            </tr>
            <tr>
                <td>Используемая память</td>
                <td><span id="memory_usage" style="color: #00ff00">0%</span></td>
            </tr>
            <tr>
                <td>Скорость сети</td>
                <td><span id="network_speed" style="color: #ffff00">0 Мбит/с</span></td>
            </tr>
            <tr>
                <td>Состояние батареи</td>
                <td><span id="battery_status" style="color: #00ff00">0%</span></td>
            </tr>
            <tr>
                <td>Полнота топлива</td>
                <td><span id="fuel_level" style="color: #00ff00">0%</span></td>
            </tr>
            <tr>
                <td>Навык управления</td>
                <td><span id="control_skill" style="color: #00ff00">0%</span></td>
            </tr>
            <tr>
                <td>Параметр стабилизации</td>
                <td><span id="stability_param" style="color: #00ff00">0%</span></td>
            </tr>
            <tr>
                <td>Уровень защиты от попаданий</td>
                <td><span id="impact_protection" style="color: #00ff00">0%</span></td>
            </tr>
            <tr>
                <td>Параметр скорости реакции</td>
                <td><span id="reaction_speed" style="color: #00ff00">0%</span></td>
            </tr>
            <tr>
                <td>Навык навигации</td>
                <td><span id="navigation_skill" style="color: #00ff00">0%</span></td>
            </tr>
            <tr>
                <td>Параметр дальности видимости</td>
                <td><span id="visibility_range" style="color: #00ff00">0%</span></td>
            </tr>
            <tr>
                <td>Уровень защиты от пожара</td>
                <td><span id="fire_protection" style="color: #00ff00">0%</span></td>
            </tr>
            <tr>
                <td>Параметр скорости перемещения</td>
                <td><span id="movement_speed" style="color: #00ff00">0%</span></td>
            </tr>
            <tr>
                <td>Навык работы с системой</td>
                <td><span id="system_skill" style="color: #00ff00">0%</span></td>
            </tr>
            <tr>
                <td>Параметр дальности связи</td>
                <td><span id="communication_range" style="color: #00ff00">0%</span></td>
            </tr>
            <tr>
                <td>Уровень защиты от воздействия окружающей среды</td>
                <td><span id="environmental_protection" style="color: #00ff00">0%</span></td>
            </tr>
            <tr>
                <td>Параметр скорости анализа ситуации</td>
                <td></td>
            </tr>
        </table>

        <script>
            function updateSystemInfo() {
                document.getElementById("cpu_load").style.color = "#ff0000";
                document.getElementById("cpu_load").innerHTML = (Math.floor(Math.random() * 100)).toString() + "%";

                document.getElementById("memory_usage").style.color = "#00ff00";
                document.getElementById("memory_usage").innerHTML = (Math.floor(Math.random() * 100)).toString() + "%";

                document.getElementById("network_speed").style.color = "#ffff00";
                document.getElementById("network_speed").innerHTML = (Math.floor(Math.random() * 1000)).toString() + " Мбит/с";

                document.getElementById("battery_status").style.color = "#ff0000";
                document.getElementById("battery_status").innerHTML = (Math.floor(Math.random() * 100)).toString() + "%";

                document.getElementById("fuel_level").style.color = "#00ff00";
                document.getElementById("fuel_level").innerHTML = (Math.floor(Math.random() * 100)).toString() + "%";

                document.getElementById("control_skill").style.color = "#ffff00";
                document.getElementById("control_skill").innerHTML = (Math.floor(Math.random() * 10)).toString();

                document.getElementById("stability_param").style.color = "#ff0000";
                document.getElementById("stability_param").innerHTML = (Math.floor(Math.random() * 10)).toString();

                document.getElementById("impact_protection").style.color = "#00ff00";
                document.getElementById("impact_protection").innerHTML = (Math.floor(Math.random() * 10)).toString();

                document.getElementById("reaction_speed").style.color = "#ffff00";
                document.getElementById("reaction_speed").innerHTML = (Math.floor(Math.random() * 10)).toString();

                document.getElementById("navigation_skill").style.color = "#ff0000";
                document.getElementById("navigation_skill").innerHTML = (Math.floor(Math.random() * 10)).toString();

                document.getElementById("visibility_range").style.color = "#00ff00";
                document.getElementById("visibility_range").innerHTML = (Math.floor(Math.random() * 100)).toString();

                document.getElementById("fire_protection").style.color = "#ffff00";
                document.getElementById("fire_protection").innerHTML = (Math.floor(Math.random() * 10)).toString();

                document.getElementById("movement_speed").style.color = "#ff0000";
                document.getElementById("movement_speed").innerHTML = (Math.floor(Math.random() * 10)).toString();

                document.getElementById("system_skill").style.color = "#00ff00";
                document.getElementById("system_skill").innerHTML = (Math.floor(Math.random() * 10)).toString();

                document.getElementById("communication_range").style.color = "#ffff00";
                document.getElementById("communication_range").innerHTML = (Math.floor(Math.random() * 100)).toString();

                document.getElementById("environmental_protection").style.color = "#ff0000";
                document.getElementById("environmental_protection").innerHTML = (Math.floor(Math.random() * 10)).toString();

                setTimeout(updateSystemInfo, 1000);
            }

            updateSystemInfo();
        </script>

    </section>

<footer>
<footer style="position: fixed;bottom: 0;width: 100%;">
    <p>2025 Denjik AI. All rights reserved.</p><a href="/">JOY</a>
</footer>
    
</footer>
</body>
</html>
)=====";
