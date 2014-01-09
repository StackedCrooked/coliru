<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/html">
<title>Coliru Viewer</title>
<head>

    <style type="text/css">

        html, body { position: relative; font-family: monospace; width: 100%; height: 100%; padding: 0; margin: 0; }
        .content { position: relative; font-family: monospace; width: 100%; height: 100%; padding: 0; margin: 0; }

        .hbox {
            display: box; display: -webkit-box; display: -moz-box; position: relative; padding: 0; margin: 0; 
            box-orient: horizontal; -webkit-box-orient: horizontal; -moz-box-orient: horizontal;
            box-align: stretch; -webkit-box-align: stretch; -moz-box-align: stretch;
        }

        .vbox {
            display: box; display: -webkit-box; display: -moz-box;
            position: relative; padding: 0; margin: 0;
            box-orient: vertical; -webkit-box-orient: vertical; -moz-box-orient: vertical;
            box-align: stretch; -webkit-box-align: stretch; -moz-box-align: stretch;
        }

        .error { background-color: #ffbbaa; }
        .f0 {
            display: box; display: -webkit-box; display: -moz-box;
            position: relative;
            box-flex: 0.0; -webkit-box-flex: 0.0; -moz-box-flex: 0.0;
        }

        .f1 { display: box; display: -webkit-box; display: -moz-box; position: relative; box-flex: 1.0; -webkit-box-flex: 1.0; -moz-box-flex: 1.0; }

        #page {
            position: relative;
            margin: 0;
            padding: 0;
            overflow: hidden;
        }

        #editor {
            position: relative;
            margin: 4px;
            padding: 4px;
        }

        pre { resize: none; position: relative; margin: 0; padding: 0;  font-size: 10pt; font-family: monospace; } 
        #cmd { margin: 4px; padding: 4px; border: solid gray; background-color: #aaffff; } 
        #output { margin: 4px; padding: 4px; border: solid gray;  } 
        #footer {
            position: relative;
            overflow: hidden;
        }

        button { margin: 2px; height: 30px; padding-left: 10px; padding-right: 10px; font-size: inherit; }

        #cloneButton   { right: 0;    top: 0; height: 30px; width: 60px;  }
        #historyButton { right: 68px; top: 0; height: 30px; width: 130px; }

        .ace_cursor {
            display: none;
        }

        .ace_cursor-layer {
            display: none;
        }

        div,textarea { outline: 0 !important; appearance: none; -webkit-appearance: none; -moz-appearance: none; }
    </style>

    <script type="text/javascript">

        var _gaq = _gaq || [];
        _gaq.push(['_setAccount', 'UA-37220775-1']);
        _gaq.push(['_trackPageview']);

        (function () {
            var ga = document.createElement('script');
            ga.type = 'text/javascript';
            ga.async = true;
            ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
            var s = document.getElementsByTagName('script')[0];
            s.parentNode.insertBefore(ga, s);
        })();

    </script>
</head>
<body>
<div id="page" class="content vbox f1">
    <div id="editor" class="f1"></div>
    <textarea type="text" id="cmd" rows='1' onkeyup='on_cmd_keyup(event);' onkeydown='on_cmd_keydown(event)' class="f0"></textarea>
    <div id="output" style="overflow:auto;" class="vbox f0"></div>

    <div id="footer" class="f0 hbox">
        <div id="path" class="f0"></div>
        <div class="f1"></div>
        <button id="cloneButton" class="f0">Edit</button>
    </div>
</div>
<script src="//d1n0x3qji82z53.cloudfront.net/src-min-noconflict/ace.js" type="text/javascript"></script>
<script>

    // Redirect www. to host domain.
    if (window.location.host.search(/^www./) === 0 || window.location.host.search(/^stacked/) === 0) {
        var host = window.location.hostname + "";
        host = host.replace(/^www./, "");
        host = host.replace(/^stacked/, "coliru.stacked");
        window.location.hostname = host;
    }


    var editor = ace.edit("editor");
    editor.setTheme("ace/theme/textmate");
    editor.commands.bindKeys({"ctrl-l":null, "left":null});
    editor.getSession().setMode("ace/mode/c_cpp");
    editor.commands.bindKeys({"ctrl-l":null}) 
    editor.commands.bindKeys({"Command-l":null}) 
    editor.setBehavioursEnabled(false);
    editor.setReadOnly(true);
    editor.clearSelection();


    var app = {};
    var url = "" + window.location.href;
    if (url.search(/\?/) !== -1) {
        app.id = url.split("?")[1].split('=')[1];
    } else {
        app.id = url.split('/A/')[1];
        if (app.id === undefined) {
            app.id = url.split('/a/')[1];
        }
    }

    if (app.id.length == 16) {
        document.getElementById('path').textContent = 'This file can be also found using the Coliru command line: cat /Archive2/' + app.id.substring(0,2) + '/' + app.id.substring(2, app.id.length) + '/main.cpp';
    }

    app.editor = editor;
    app.output = document.getElementById("output");
    app.output.readOnly = true;
    app.output.data = "Fetching data....";
    app.cmd_field = document.getElementById("cmd");


    app.send = function (location, post_data, f) {

        var httpRequest = new XMLHttpRequest();
        var url = "http://" + window.location.hostname + ":" + window.location.port + '/' + location;

        httpRequest.open("GET", url, true);
        httpRequest.onreadystatechange = function () {
            if (httpRequest.readyState == 4) {
                if (httpRequest.status == 200) {
                    f(httpRequest.responseText.trim());
                }
            }
        };
        httpRequest.send(post_data);
    };

    app.send("archive?id=" + app.id, "", function (response) {
        var obj = JSON.parse(response);
        app.editor.setValue(obj.src);
        app.editor.getSession().setScrollLeft(0);
        app.cmd = obj.cmd;
        app.cmd_field.value = obj.cmd;
        app.cmd_output = obj.output.trim();
        var lines = app.cmd_output.split(/\n/);
        app.cmd_field.rows = app.cmd.split(/\n/).length;
        console.log("rows=" + app.cmd.split(/\n/).length);
        var pre_open = "<pre class='f0' onclick='window.jumpToError(this)' onmouseover='window.highlightError(this, true)' onmouseout='window.highlightError(this, false)' style='display: block; margin:0; padding:0; '>";
        var pre_close = "</pre>";
        var text = "";
        var new_line = true;
        for (var i = 0; i !== lines.length; ++i) {
            var line = lines[i];
            if (line !== '') {
                    if (line.search(/^\w+.cpp:\d+:\d+/) !== -1) {
                        text += pre_open.replace(/f0/, "f0 error") + line.replace(/</g, '&lt').replace(/>/g, '&gt') + pre_close;
                    } else {
                        text += pre_open + line.replace(/</g, '&lt').replace(/>/g, '&gt') + pre_close;
                    }
                } else {
                text += '<br/>';
            }
        }

        app.output.innerHTML = text;
        app.output_text = obj.output;

        try { document.domain = "coliru.stacked-crooked.com"; } catch (e) { console.log("Caught: " + e); }
        var getHistory = function () {
            var historyObj = localStorage['history_items'];
            if (historyObj === undefined) {
                console.log("History object is undefined. So create it.");
                historyObj = '{}';
            } else if (historyObj === null) {
                console.log("History object returns null. Clearing the history.");
                localStorage.clear();
                historyObj = '{}';
            }
            return JSON.parse(historyObj);
        };
        app.history = getHistory();

        if (app.history["" + app.id] === undefined)
        {
            obj['timestamp'] = "" + Date.now();
            obj['id'] = app.id;
            obj['url'] = "" + window.location;
            obj['output'] = app.output_text;
            app.history["" + app.id] = obj;
            //localStorage['history_items'] = JSON.stringify(app.history);
        }

        window.setTimeout(function () {
            var ace_lines = document.getElementsByClassName("ace_line");
            var i;
            for (i = 0; i !== ace_lines.length; ++i) {
                ace_lines[i].style.color = "inherit";
            }
            var output_lines = app.output_text.split(/\n/);
            for (i = 0; i != output_lines.length; ++i) {
                try {
                    var line = output_lines[i];
                    if (line.search(/^\w+.cpp:\d+:\d+/) !== -1) {
                        var lineno = parseInt(line.split(":")[1]);
                        ace_lines[lineno - 1].style.color = "red";
                    }
                }
                catch (e) {
                    console.log(JSON.stringify(e));
                }
            }
        }, 100);


        app.editor.clearSelection();
        app.editor.scrollToRow(0);
    });

    app.goBack = function () {
        localStorage.setItem("src", editor.getValue());
        localStorage.setItem("cmd", app.cmd);
        window.location.href = "/";
    };
    window.highlightError = function(node, b) {
        if (node.textContent.search(/^\w+.cpp:\d+:\d+/) === -1) {
            return;
        }
        node.style.cursor = b ? 'pointer' : 'auto';
    };
    window.jumpToError = function(node) {

        var line = node.textContent;
        if (line.search(/^\w+.cpp:\d+:\d+/) !== -1) {
            var components = line.split(":");
            var lineno = parseInt(components[1]);
            var col = parseInt(components[2]) - 1;
            app.editor.gotoLine(lineno, col, true);
            app.editor.focus();
        }
    };

    document.getElementById("cloneButton").onclick = app.goBack;

</script>
</body>
</html>
