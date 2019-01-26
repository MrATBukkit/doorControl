function setStatus() {
	axios.get('/status').then(function(response) {
		document.querySelector('.status').innerHTML = response.data? 'Öffnen': 'Schließen';
		if (response.data) {
			document.querySelector('#toggle').classList.add('btn-danger');
			document.querySelector('#toggle').classList.remove('btn-success');
		} else {
			document.querySelector('#toggle').classList.add('btn-success');
			document.querySelector('#toggle').classList.remove('btn-danger');
		}
	}).catch(() => {
		document.querySelector('.status').innerHTML = 'Fehler';
	});
}
setStatus();
setInterval(setStatus, 3000);
document.querySelector('#toggle').addEventListener('click', function() {
	axios.get('/toggle').then(function(response) {
		console.log('toggle');
	});
});