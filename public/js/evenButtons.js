// Set default lamp status
let status;

// Save oroginal button
const btn = document.getElementById('lamp');
const oriBtn = btn.innerHTML;

// Get inisial lamp status
document.addEventListener('DOMContentLoaded', async function () {
	console.log('Get lamp status');
	// Disable the button
	btn.disable = true;
	btn.innerHTML = `
		<span class="spinner-border spinner-border-sm" aria-hidden="true"></span>
		<span role="status">Loading...</span>
	`;

	// Request data from API
	try {
		const response = await fetch('/api/lamp-status', {
			method: 'GET',
			headers: {
				'Accept': 'application/json',
				'Content-Type': 'application/json'
			}
		});

		// Recive data
		const data = await response.json();
		status = data.status;
		document.querySelector('#lamp').textContent = status === 'ON' ? 'Turn OFF' : 'Turn ON';
		console.log('Current Status', status);

		// Enabled the  buuton
		btn.disable = false;
		btn.innerHTML = oriBtn;
	} catch (error) {
		console.error('Error', error);
	} finally {
		btn.disable = false;
		btn.textContent = status === 'ON' ? 'Turn OFF' : 'Turn ON';
	}
})

// set new status
async function toggleStatus() {
	// Get current status
	const currStat = btn.getAttribute('data-status');
	const newStatus = currStat === 'OFF' ? 'ON' : 'OFF';
	
	// Disable the button
	btn.disable = true;
	btn.innerHTML = `
		<span class="spinner-border spinner-border-sm" aria-hidden="true"></span>
		<span role="status">Loading...</span>
	`;

	// request chang lamp status to API
	try {
		const response = await fetch('/api/lamp-status', {
			method: 'POST',
			headers: {
				'Accept': 'application/json',
				'Content-Type': 'application/json'
			},
			body: JSON.stringify({status: newStatus})
		});

		// Recive data
		const data = await response.json();
		status = data.status;
		btn.setAttribute('data-status', data.status);
		btn.textContent = data.status === 'ON' ? 'Turn OFF' : 'Turn ON';

	} catch (error) {
		console.error('Error: ', error);
	} finally {
		btn.disable = false;
		btn.textContent = status === 'ON' ? 'Turn OFF' : 'Turn ON';
	}
}

