var plugin;

$(document).ready(function() {
	$('#submitRegistration').click(submitRegistration);
	$('#submitLogin').click(submitLogin);

	plugin = document.getElementById('plugin0');
	loadProfiles();
});

function loadProfiles() {
	var profiles = plugin.getProfiles();
	var selectBox = $('#profile');
	selectBox.empty();
	$.each(profiles, function(index, key) {
		selectBox.append($('<option value="' + index + '"></option>').text(key));
	});
}

function submitRegistration() {
	$('#register-publicKey').val(plugin.registerProfile($('#profile').val()));
}

function submitLogin() {
	var digest = "sLAdBrWHiS+qszo8E0bZlM/FvMn1CVILirS6WoJdgQK6fpM7LXzH4zEKeX1/5wOZ\n" +
		"FBvpSWQ7Ur36tMIQnRlxqPdcx9GMpDkiXMI7aggpKPRnwkFtYCmVRl/kn+LzxSzA\n" +
		"VU3d/ppKdl2i2ZVJK1JrwrAADAo8XteZg3WPlAAJtmZY+ZjaSt/ECEspUm5DzVJg\n" +
		"RDjD2qlzPTGWHWVz+AZ6dixAxhtWPt0ArkVakPSoQ+HqXJ9YwvIy6RjmOfKiKu4F\n" +
		"FW+TfZ+YImiL5iqxijZjRmXSsTeoBILd14aD7BmpPEC+hO5ezeCPcKBdP98Fawhe\n" +
		"YNzMpsEIjxFRHhk7tHGMqg==\n";
		
	// Ping the server to get the profile ID for the handle and a digest
	
	// Use the handle to encrypt the data
	$('#register-cipher').val(plugin.authenticateProfile('ad13', digest));

	return false;
}