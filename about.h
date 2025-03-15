const char *ABOUT_HTML_CONTENT = R"=====(
<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
    <title>О проекте</title>
    <style>
        body {
            font-family: "Courier New", Courier, monospace;
            background-color: #000;
            color: #0f0;
            margin: 0;
            padding: 10px;
            overflow: hidden;
            width: 388px;
            height: 675px;
        }
        header {
            background-color: #222;
            color: #0f0;
            padding: 10px;
            text-align: center;
            border-bottom: 2px solid #0f0;
        }
        h1 {
            font-size: 1.5em;
            margin: 0;
        }
        section {
            padding: 10px;
        }
        h2 {
            font-size: 1.3em;
            margin-bottom: 10px;
            color: #0f0;
            border-bottom: 1px solid #0f0;
        }
        p {
            font-size: 1.1em;
            line-height: 1.5em;
            margin: 10px 0;
        }
        .highlight {
            color: #f0f;
        }
        footer {
            position: absolute;
            bottom: 10px;
            width: 100%;
            font-size: 0.8em;
            text-align: center;
            color: #888;
        }
        a {
            color: #0ff;
            text-decoration: none;
        }
        a:hover {
            color: #fff;
        }
    </style>
</head>
<body>
    <header>
        <h1>Машинка Проекта Denjik</h1>
    </header>

    <section>
        <h2>О проекте</h2>
        <p>
            Добро пожаловать в удивительный мир <span class="highlight">машинки будущего</span>, созданной на базе новейших технологий ESP8266 и L298N! 
            Эта маленькая чудо-машина оснащена умными датчиками и управляется с помощью мощного веб-интерфейса. 
            Благодаря магическим возможностям нашего времени, она может перемещаться, как по воздуху, принимая команды от вас через веб-браузер.
        </p>
        <p>
            Этот проект — плод страсти и вдохновения, поддержанный моими самыми близкими: <span class="highlight">Любимой Яночкой</span>, 
            очаровательной <span class="highlight">доченькой Николь</span>, всей семьей и друзьями-программистами. 
            И, конечно, благодарность за помощь идет и к тебе, моя верная <span class="highlight">Нейросеточка</span>!
        </p>
    </section>

    <footer>
        <p>© 2025 <span class="highlight">Denjik</span> AI. All rights reserved. <a href="/">JOY</a></p>
    </footer>
</body>
</html>
)=====";
