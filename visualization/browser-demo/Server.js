var fs = require("fs");
var express = require("express");
var app = express();

app.get('/', function (req, res){
    res.sendFile(__dirname + '/index.html');
});

app.get('/draw3DPlot.js', function (req, res){
	fs.readFile("./draw3DPlot.js", function (err, content) {
		if (err) { res.end(); return; }
		res.writeHeader(200, {"Content-Type": "text/js"});
		res.write(content);
		res.end();
	});
});

app.get('/drawMap.js', function (req, res){
	fs.readFile("./drawMap.js", function (err, content) {
		if (err) { res.end(); return; }
		res.writeHeader(200, {"Content-Type": "text/js"});
		res.write(content);
		res.end();
	});
});

app.get('/styles.css', function (req, res){
	fs.readFile("./styles.css", function (err, content) {
		if (err) { res.end(); return; }
		res.writeHeader(200, {"Content-Type": "text/css"});
		res.write(content);
		res.end();
	});
});

var PORT=3000;
app.listen(PORT, function() {
	console.log("Listening on port " + PORT);
});
