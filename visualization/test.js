var fs = require("fs");
var admin = require('firebase-admin');

admin.initializeApp({
	credential: admin.credential.applicationDefault(),
	databaseURL: 'https://spaspect-dashboard.firebaseio.com'
});
const db = admin.firestore();
const dbUsers = db.collection('users');
const dbDashboards = db.collection('dashboards');

id = "d3c4fd41-8892-453b-bc00-64d1f494284b"
var content = fs.readFileSync("<wherever you have the Greece json stored locally>");
dbDashboards.doc(id).set(JSON.parse(content));


dbDashboards.doc(id).get().then((doc) => {
	if (doc.exists) {
		var dashboardData = doc.data();

		console.log(doc._updateTime);
	}
});

/*var content = fs.readFileSync("/home/ravit/Konect-Code/spaspect-project/spaspect/visualization/GreeceCam.json");
dbDashboards.doc(id).set(JSON.parse(content));*/
