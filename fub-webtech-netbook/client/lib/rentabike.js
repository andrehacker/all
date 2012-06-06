var customerLoaded = false;
var customerData = undefined;
var ajaxCount = 0;
/*
 ******
 HELPER FUNCTIONS
 ******
*/

function $N(name) {
	return $A(document.getElementsByName(name));
}

function AjaxRequest (url, parms) {

	new Ajax.Request(url, parms);
	
	try {
		ajaxCount ++;
		$('ajaxCounter').innerHTML = "Ajax calls: " + ajaxCount;
	} catch(ex) {
		//
	}
}

function updatePageHeader(name, description) {
	try {
		$('systemAlers').update('');		// Quick fix. Better move this to new function
		var templateHeader = new Template($('template_page_header').innerHTML);
		var headerHTML = templateHeader.evaluate({ 'pagename': name, 'description': description });
		$('page_header').update(headerHTML);
	} catch(ex) {
		//
	}
}

function showLoader(name) {
	try {
		//$(name).style.display = 'block';
		$(name).show();
	} catch (ex) {
	
	}
}

function hideLoader(name) {
	try {
		//$(name).style.display = 'none';
		$(name).hide();
	} catch (ex) {
	
	}
}


function addslashes (str) {
    // discuss at: http://phpjs.org/functions/addslashes
    return (str + '').replace(/[\\"']/g, '\\$&').replace(/\u0000/g, '\\0');
}
function stripslashes (str) {
    return (str + '').replace(/\\(.?)/g, function (s, n1) {
        switch (n1) {
        case '\\':
            return '\\';
        case '0':
            return '\u0000';
        case '':
            return '';
        default:
            return n1;
        }
    });
}

/*
 ******
 ONLOAD
 ******
*/
document.observe("dom:loaded", function() {
	
	// Show page title
	updatePageHeader('Welcome','Renting bikes was never easier!');
	
	$('frmLogin').observe('submit', frmLogin);
	// Is Customer already logged in?
	if(customerLoaded == false){
		checkLogin();
	}

	// Menu click events
	$$('.bikeinfo').map(function(ele){ele.observe('click', loadBikeInfo);});
	$('linkRent').observe('click', loadRent);
	$('linkReturn').observe('click', loadReturn);
	$('linkAdminBikes').observe('click', loadAdminBikes);
	$('linkAdminBikeCats').observe('click', loadBikeCats);
	$('linkAdminCustomer').observe('click', loadCustomer);
	$('linkAdminInvoice').observe('click', loadInvoice);
	$('linkRegistered').observe('click', registrationLoad);
	$$('.stats').map(function(ele){ele.observe('click', loadStats);});
	
	
	
	// *** LISTENERS FOR NEW BIKE MODAL ***
	// May be done only one time - so here in document load
	
	// Create listeners for modal views
	jQuery('#modal_new_bike').bind('show', function() {
		$('new_bike_form').reset();
	} );
	jQuery('#modal_new_bike').bind('hide', function(event) {
		// TODO: check if user has entered data. Then ask if really want to quit
		// event.stop();
	} );
	jQuery('#modal_new_bike').bind('shown', function() {
		// prepare form = set focus
		$('new_bike_name').focus();
	} );
	
	jQuery('#modal_new_bikecat').bind('show', function() {
		$('new_bikecat_form').reset();
	} );
	jQuery('#modal_new_bikecat').bind('hide', function(event) {
		// TODO: check if user has entered data. Then ask if really want to quit
		// event.stop();
	} );
	jQuery('#modal_new_bikecat').bind('shown', function() {
		// prepare form = set focus
		$('new_bikecat_name').focus();
	} );
	
	// Modal form submitting handling
	$('new_bike_form').observe('submit', function(event) {
		event.stop();	// Stop event = don't submit form!
		
		// Send new bike to server, reload list!
		showLoader('ajax_loader_modal_bike');
		AjaxRequest('/ajax/Admin/addbike', {
			method:'post',
			parameters: $('new_bike_form').serialize(true),
			onSuccess: function (response) {
				hideLoader('ajax_loader_modal_bike');
				jQuery('#modal_new_bike').modal('hide');
				loadAdminBikes();	// reload view with new bike!
			},
			onFailure: function () {
				$('main_content').update('AJAX Error adding bike');
				jQuery('#modal_new_bike').modal('hide');
				hideLoader('ajax_loader_modal_bike');
			}
		});
	});
	$('new_bikecat_form').observe('submit', function(event) {
		event.stop();	// Stop event = don't submit form!
		
		// Send new bike to server, reload list!
		showLoader('ajax_loader_modal_bikecat');
		AjaxRequest('/ajax/Admin/addbikecat', {
			method:'post',
			parameters: $('new_bikecat_form').serialize(true),
			onSuccess: function (response) {
				hideLoader('ajax_loader_modal_bikecat');
				jQuery('#modal_new_bikecat').modal('hide');
				loadBikeCats();	// reload view with new bike cat!
			},
			onFailure: function () {
				$('main_content').update('AJAX Error adding bike cat');
				jQuery('#modal_new_bikecat').modal('hide');
				hideLoader('ajax_loader_modal_bikecat');
			}
		});
	});
	
	$('new_bike_cancel').observe('click', function() {
		// TODO: Ask if user really want to quit (if he entered data)
		// hide modal view
		jQuery('#modal_new_bike').modal('hide');
	});
	$('new_bikecat_cancel').observe('click', function() {
		// TODO: Ask if user really want to quit (if he entered data)
		// hide modal view
		jQuery('#modal_new_bikecat').modal('hide');
	});
});








/*
 ******
 BIKE INFO
 ******
*/
function loadBikeInfo(event) {
	
	updatePageHeader('Info','Bikes and Information');
	
	showLoader('ajax_loader');
	AjaxRequest('/ajax/Admin/loadbikes', {
		method:'get',
		onSuccess: function (response) {
			var obj = response.responseText.evalJSON();
			$('main_content').update ( response.responseText );
	
			// Build table body = rows
			var body = '';
			var templateBody = new Template($('template_row_bikeinfo').value);
			for (var i=0; i<obj.length; i++) {
				body += templateBody.evaluate(obj[i]);
			}

			// Build whole table
			var templateTable = new Template($('template_table_bikeinfo').value);
			var tableHTML = templateTable.evaluate({ rows: body });
			$('main_content').update ( tableHTML );
			
			hideLoader('ajax_loader');
		},
		onFailure: function () {
			$('main_content').update('AJAX Error');
			hideLoader('ajax_loader');
		}
	});
	return false;
}



/*
 ******
 RENT
 ******
*/
var geocoder;
var markers = new Array();
var map;
var infoWindow = new google.maps.InfoWindow({
	content: "Bike Info coming soon..."
});

// LAT/LONG FINDER: http://www.linkr.de/2009/03/24/mit-google-maps-laengen-breitengrade-ermitteln-freies-geocoding-skript/
// Multiple markers: http://you.arenot.me/2010/06/29/google-maps-api-v3-0-multiple-markers-multiple-infowindows/
// Blog about InfoWindows: http://www.svennerberg.com/2009/09/google-maps-api-3-infowindows/
function loadRent() {
	
	updatePageHeader('Find a bike','... and click on it to rent it');

	// Load div for map
	$('main_content').update($('template_map').value);
	
	// Show google map
	var latlngBerlin = new google.maps.LatLng(52.51, 13.40);
	var myOptions = {
		zoom: 12,
		center: latlngBerlin,
		mapTypeId: google.maps.MapTypeId.ROADMAP
	};
	map = new google.maps.Map(document.getElementById("map_canvas"), myOptions);
	
	// Geocoding - Init Location finder
	geocoder = new google.maps.Geocoder();
	$('form_address').observe('submit', function (event) {
		event.stop();	// stop submitting form!
		var address = $("text_address").value;
		if (geocoder) {
			geocoder.geocode( { 'address': address}, function(results, status) {
				if (status == google.maps.GeocoderStatus.OK) {
					map.setCenter(results[0].geometry.location);
					/*var marker = new google.maps.Marker({
						map: map, 
						position: results[0].geometry.location
					});*/
				} else {
					alert("Geocode was not successful for the following reason: " + status);
				}
			});
		}
	});
	
	// Load bikes and add to map (Future: add only the ones in shown area)
	AjaxRequest('/ajax/Admin/loadbikes', {
		method:'get',
		onSuccess: function (response) {
			var bikes = response.responseText.evalJSON();
			for (var i=0; i<bikes.length; i++) {
				if (bikes[i].isRented == true) {
					continue;	// hide rented bikes
				}
				var marker = new google.maps.Marker({
					position: new google.maps.LatLng(bikes[i].position_lat, bikes[i].position_long),
					map: map,
					title: bikes[i].name,
					bike_id: bikes[i].id,	// CUSTOM FIELDS!
					bike_name: bikes[i].name,
					bike_description: bikes[i].description,
					bike_category: bikes[i].category,
					bike_price: bikes[i].price,
					bike_img_url: bikes[i].img_url,
					bike_position_lat: bikes[i].position_lat,
					bike_position_long: bikes[i].position_long
				});
				// Add Listener
				google.maps.event.addListener(marker, 'click', function () {
					var templateInfo = new Template($('template_infowindow').value);
					var html = templateInfo.evaluate({
						bike_id: this.bike_id,
						bike_name: this.bike_name,
						bike_description: this.bike_description,
						bike_category: this.bike_category,
						bike_price: this.bike_price
					});
					//infoWindow.setContent('bikeid: ' + this.bike_id);
					infoWindow.setContent(html);
					infoWindow.close();
					infoWindow.open(map, this);
				});
				markers.push(marker);
			}
		},
		onFailure: function () {
			alert('Error loading bike markers');
		}
	});
	
	// Register to some events
	google.maps.event.addListener(map, 'click', function() {
		
		infoWindow.close();	// close if open
	});
}

function clickBook(id) {
	// Get Bike Infos out of marker info (no server request).
	// Finall confirmation transaction will ensure that bike is still available
	
	// Get reference to marker
	var curMarker = null;
	for (var i=0; i<markers.length; i++) {
		if (markers[i].bike_id == id) {
			curMarker = markers[i];
			break;
		}
	}
	updatePageHeader('Renting confirmation',' ');
	
	// Show new content
	var templateRent = new Template($('template_rent_confirm').value);
	$('main_content').update(templateRent.evaluate(curMarker));
}

function onRentConfirm(event, bike_id) {
	event.stop();
	
	// Send confirmation request to server
	// TODO: Handle case where bike was booked in the meantime
	
	showLoader('ajax_loader');
	AjaxRequest('/ajax/Rent/start', {
		method:'post',
		parameters: {txtBikeId: bike_id},
		onSuccess: function (response) {
			// Renting was successfull
			var obj = alertManagerGetAjaxResponse(response);
			//alert("Bike ID " + obj.Invoice[0].BikeId);
			if (obj.Invoice != undefined) {
				var template = new Template($('template_rent_success').value);
				var html = template.evaluate(obj.Invoice[0]);
				$('main_content').update ( html );
			}
			
			hideLoader('ajax_loader');
		},
		onFailure: function () {
			$('main_content').update('AJAX Error');
			hideLoader('ajax_loader');
		}
	});
}

function onRentCancel() {
	loadRent();
}

function onRentAfterConfirm () {
	loadRent();
}

/*
 ******
 RETURN
 ******
*/

function loadReturn() {
	// Check if user rent something
	
	updatePageHeader('Return your bike',' ');
	
	showLoader('ajax_loader');
	AjaxRequest('/ajax/Rent/info', {
		method:'get',
		onSuccess: function (response) {
			var inv = alertManagerGetAjaxResponse(response);
			if (inv.length != undefined) {
				inv = inv[0];	// returns array with single item
				// Get Bike Info of returned bike now!
				AjaxRequest('/ajax/Admin/loadbike', {
					method:'post',
					parameters: {id: inv.BikeId},
					onSuccess: function (response) {
						if (inv.status == 0) {	// bike rent
							hideLoader('ajax_loader');
							var bike = alertManagerGetAjaxResponse(response);
							// calculate current_total and minutes_rent
							var startDate = new Date(inv.rent_start);
							bike.minutes_rent = (((new Date()).getTime()-startDate.getTime()) /(1000*60)).toFixed(0);
							
							bike.current_total = (bike.price * bike.minutes_rent * 0.01).toFixed(2);
							// show bike to return
							var template = new Template($('template_return').value);
							var html = template.evaluate(bike);
							$('main_content').update ( html );
						}
					},
					onFailure: function () {
						$('main_content').update('AJAX Error returning bike');
						hideLoader('ajax_loader');
					}
				});
			}
			else {	// no bike rent
				$('main_content').update ( $('template_return_no_bike').value );
			}
			
			hideLoader('ajax_loader');
		},
		onFailure: function () {
			$('main_content').update('AJAX Error');
			hideLoader('ajax_loader');
		}
	});
}

function onReturnConfirm(event, bike_id) {
	event.stop();
	showLoader('ajax_loader');
	AjaxRequest('/ajax/Rent/end', {
		method:'get',
		onSuccess: function (response) {
			// Renting was successfull
			var obj = alertManagerGetAjaxResponse(response);
			if (obj.length != undefined) {
				var template = new Template($('template_return_success').value);
				var html = template.evaluate(obj[0]);
				$('main_content').update ( html );
			}
			
			hideLoader('ajax_loader');
		},
		onFailure: function () {
			$('main_content').update('AJAX Error');
			hideLoader('ajax_loader');
		}
	});
}

function onReturnAfterConfirm() {
	loadRent();
}


/*
 ******
 ADMIN - BIKES
 ******
*/
function loadAdminBikes(event) {
	
	updatePageHeader('Administration','Manage your bikes');
	
	if (event) {	// may be called without any event
		//Event.stop(event);
	}
	showLoader('ajax_loader');
	AjaxRequest('/ajax/Admin/loadbikes', {
		method:'get',
		onSuccess: function (response) {
			var obj = response.responseText.evalJSON();

			// Build table body = rows
			var body = '';
			var templateBody = new Template($('template_row_bike').value);
			for (var i=0; i<obj.length; i++) {
				body += templateBody.evaluate(obj[i]);
			}

			// Build whole table
			var templateTable = new Template($('template_table_bike').value);
			var tableHTML = templateTable.evaluate({ rows: body });
			$('main_content').update ( tableHTML );

			// Listen on New Bike Button click
			// (don't use functionality of bootstrap-modal plugin)
			$('button_new_bike').observe('click', clickNewBike);
	
			// Listen on delete bike clicks
			var buttons = $N('button_delete_bike');
			for(var i=0; i<buttons.length; i++) {
				buttons[i].observe('click', clickDeleteBike);
			}
			$('button_new_bike').focus();
			hideLoader('ajax_loader');
		},
		onFailure: function () {
			$('main_content').update('AJAX Error');
			hideLoader('ajax_loader');
		}
	});
	return false;
}

function clickNewBike() {
	// Load categories for new bike and update modal view
	AjaxRequest('/ajax/Admin/loadbikecats', {
		method:'get',
		onSuccess: function (response) {
			// Update modal view
			var obj = response.responseText.evalJSON();

			// Build table body = rows
			var radios = '';
			var templateRadio = new Template($('template_radio_bikecat').value);
			for (var i=0; i<obj.length; i++) {
				radios += templateRadio.evaluate(obj[i]);
			}
			$('new_bike_cat_div').update(radios);
			
			// Show modal view
			jQuery('#modal_new_bike').modal({
				backdrop: true,
				keyboard: true,
				show: true
			});
		},
		onFailure: function () {
			$('main_content').update('AJAX Error deleting bike');	// TODO: show errors in separate div!
			hideLoader('ajax_loader');
		}
	});
}

function clickDeleteBike(event) {
	
	// Send delete request to server and reload list
	showLoader('ajax_loader');
	AjaxRequest('/ajax/Admin/deletebike', {
		method:'post',
		parameters: {id: Event.findElement(event).title},
		onSuccess: function (response) {
			hideLoader('ajax_loader');
			loadAdminBikes();	// reload view with new bike!
		},
		onFailure: function () {
			$('main_content').update('AJAX Error deleting bike');	// TODO: show errors in separate div!
			hideLoader('ajax_loader');
		}
	});
}





/*
 ******
 ADMIN - BIKE CATEGORIES
 ******
*/
function loadBikeCats(event) {
	
	updatePageHeader('Administration','Manage your bike categories');
	
	if (event) {	// may be called without any event
		//Event.stop(event);
	}
	showLoader('ajax_loader');
	AjaxRequest('/ajax/Admin/loadbikecats', {
		method:'get',
		onSuccess: function (response) {
			var obj = response.responseText.evalJSON();
			$('main_content').update ( response.responseText );
	
			// Build table body = rows
			var body = '';
			var templateBody = new Template($('template_row_bikecat').value);
			for (var i=0; i<obj.length; i++) {
				body += templateBody.evaluate(obj[i]);
			}

			// Build whole table
			var templateTable = new Template($('template_table_bikecat').value);
			var tableHTML = templateTable.evaluate({ rows: body });
			$('main_content').update ( tableHTML );

			// Listen on New Bike Cat Button click
			$('button_new_bikecat').observe('click', clickNewBikeCat);
	
			// Listen on delete bikecat clicks
			var buttons = $N('button_delete_bikecat');
			for(var i=0; i<buttons.length; i++) {
				buttons[i].observe('click', clickDeleteBikeCat);
			}
			$('button_new_bikecat').focus();
			hideLoader('ajax_loader');
		},
		onFailure: function () {
			$('main_content').update('AJAX Error');
			hideLoader('ajax_loader');
		}
	});
	return false;
}

function clickNewBikeCat() {
	// show modal view
	jQuery('#modal_new_bikecat').modal({
		backdrop: true,
		keyboard: true,
		show: true
	});
}

function clickDeleteBikeCat(event) {
	
	// Send delete request to server and reload list
	showLoader('ajax_loader');
	AjaxRequest('/ajax/Admin/deletebikecat', {
		method:'post',
		parameters: {id: Event.findElement(event).title},
		onSuccess: function (response) {
			hideLoader('ajax_loader');
			loadBikeCats();	// reload list!
		},
		onFailure: function () {
			$('main_content').update('AJAX Error deleting bike cat');	// TODO: show errors in separate div!
			hideLoader('ajax_loader');
		}
	});
}

/*
 ******
 ADMIN - Customer
 ******
*/
function loadCustomer(event) {
	
	updatePageHeader('Administration','Manage your Customers');
	
	if (event) {	// may be called without any event
		//Event.stop(event);
	}
	showLoader('ajax_loader');
	AjaxRequest('/ajax/Customer/list', {
		method:'get',
		onSuccess: loadCustomerSuccess,
		onFailure: function () {
			$('main_content').update('AJAX Error');
			hideLoader('ajax_loader');
		}
	});
	return false;
}

function loadCustomerSuccess (response) {
	// $('main_content').update(response.responseText);		// show received JSON
	var obj = alertManagerGetAjaxResponse(response);//response.responseText.evalJSON();

	// Build table body = rows
	var body = '';
	var templateBody = new Template($('template_row_customer').value);
	for (var i=0; i<obj.length; i++) {
		body += templateBody.evaluate(obj[i]);
	}

	// Build whole table
	var templateTable = new Template($('template_table_customer').value);
	var tableHTML = templateTable.evaluate({ rows: body });
	$('main_content').update ( tableHTML );

	hideLoader('ajax_loader');
}

function clickNewCustomer() {
	var obj = new Array();
	obj[0] = new Object();
	obj[0].action_label = "Create";
	obj[0].name = "";
	obj[0].password = "";
	obj[0].address = "";
	obj[0].isAdmin = "";
	
	// Build table body = rows
	var body = '';
	var templateBody = new Template($('modal_customer').innerHTML);
	for (var i=0; i<obj.length; i++) {
		body += templateBody.evaluate(obj[i]);
	}
	// Build whole table
	$('modal_customer_viewer').update ( body );
	hideLoader('ajax_loader');
	
	// show modal view
	jQuery('#modal_customer_viewer').modal({
		backdrop: true,
		keyboard: true,
		show: true
	});
}

function clickDeleteCustomer(CustomerId) {
	
	// Send delete request to server and reload list
	showLoader('ajax_loader');
	AjaxRequest('/ajax/Customer/delete', {
		method:'post',
		parameters: {'txtCustomerId': CustomerId},
		onSuccess: function (response) {
			hideLoader('ajax_loader');
			loadCustomer();// reload view with new bike!
		},
		onFailure: function () {
			// TODO: show errors in separate div!
			$('main_content').update('AJAX Error deleting Customer');	
			hideLoader('ajax_loader');
		}
	});
}

function clickUpdateCustomer(customerId){
	showLoader('ajax_loader');
	AjaxRequest('/ajax/Customer/info', {
		method:'post',
		parameters: {'txtCustomerId': customerId},
		onSuccess: loadCustomerUpdateSuccess,
		onFailure: function () {
			$('main_content').update('AJAX Error');
			hideLoader('ajax_loader');
		}
	});	
}
function loadCustomerUpdateSuccess(response){
	var obj = alertManagerGetAjaxResponse(response);//response.responseText.evalJSON();
	obj[0].action_label = "Update"
	
	// Build table body = rows
	var body = '';
	var templateBody = new Template($('modal_customer').innerHTML);
	for (var i=0; i<obj.length; i++) {
		obj[i].isadmin = (obj[i].isAdmin == 1 || obj[i].isAdmin == true || obj[i].isAdmin == "true") ? 'checked=\"checked\"' : "";
		body += templateBody.evaluate(obj[i]);
	}
	// Build whole table
	$('modal_customer_viewer').innerHTML =  body;
	hideLoader('ajax_loader');
	
	// show modal view
	jQuery('#modal_customer_viewer').modal({
		backdrop: true,
		keyboard: true,
		show: true
	});
}

function formCustomer(event, action_label){
	if (event) {	// may be called without any event
		Event.stop(event);
	}
	if(action_label=="Create"){
		action = "create";
	}
	else if(action_label=="Update"){
		action = "update";
	}
		// Send new bike to server, reload list!
		showLoader('modal_customer_viewer');
		AjaxRequest('/ajax/Customer/' + action, {
			method:'post',
			parameters: $('new_customer_form_'+action_label).serialize(true),
			onSuccess: function (response) {
				alertManagerGetAjaxResponse(response);
				hideLoader('ajax_loader_customer');
				jQuery('#modal_customer_viewer').modal('hide');
				loadCustomer();	// reload view with new bike cat!
			},
			onFailure: function () {
				alertManagerGetAjaxResponse(response);
				jQuery('#modal_customer_viewer').modal('hide');
				hideLoader('modal_customer_viewer');
			}
		});
	
	return false;
}


/*

 Alert Manager

*/
function alertManagerGetAjaxResponse(response){
	var obj = response.responseText.evalJSON();
	if(obj.failure != undefined)
		alertRender('failure', obj.failure)
	if(obj.success != undefined)
		alertRender('success', obj.success)
	return obj;
}
function alertRender(type, message){
	//type = warning, error, success, info
	if(type == 'failure')
		type = 'error';
	var html = '<div class=\"alert-message #{type}\" data-alert=\"alert\"><a class=\"close\" href=\"#\">×</a><p>#{message}</p></div>';
	var templateHeader = new Template(html);
	var headerHTML = templateHeader.evaluate({ 'type': type, 'message': message });
	$('systemAlers').innerHTML += headerHTML;
}

/* 

 Login / Logout

*/

function frmLogin(event){
	if (event) {	// may be called without any event
		Event.stop(event);
	}
	Event.stop(event);
	AjaxRequest('/ajax/login/', {
			method:'post',
			parameters: $('frmLogin').serialize(true),
			onSuccess: function (response) {
				var obj = alertManagerGetAjaxResponse(response);
				if(obj.customer != undefined){
					customerLoaded = true;
					customerData = obj.customer;
					loadNav();
				}
			},
			onFailure: function () {
				var obj = alertManagerGetAjaxResponse(response);
			}
		});
	return false;
}

function clickLogout(){
	customerLoaded = false;
	customerData = undefined;
	loadNav();
	AjaxRequest('/ajax/logout/', {
			onSuccess: function (response) {
				var obj = alertManagerGetAjaxResponse(response);
			},
			onFailure: function () {
				var obj = alertManagerGetAjaxResponse(response);
			}
		});
	loadBikeInfo();
}
function checkLogin(){
	AjaxRequest('/ajax/login/info', {
			onSuccess: function (response) {
				var obj = response.responseText.evalJSON();
				//Customer is logged in
				alreadyLoggedIn(obj);
			},
			onFailure: function () {
				//var obj = response.responseText.evalJSON();				
			}
		});
}

function alreadyLoggedIn(obj){
	if(obj.customer != undefined){
		customerLoaded = true;
		customerData = obj.customer;
		loadNav();
	}
}

/*

 Change Navigation

*/
function loadNav(){
	if(customerLoaded){
		$('publicCustomer').hide();
		$('loggedinCustomer').show();
		if(customerData.isAdmin){
			$('loggedinIsAdmin').show();
		}
		else{
			$('loggedinIsAdmin').hide();
		}
		$('displayCustomerName').innerHTML = "Hallo <b>" + customerData.name + "</b>";
	}
	else{
		$('publicCustomer').show();
		$('loggedinCustomer').hide();
	}
}

/*

 Registration

*/

function registrationLoad(){
	showLoader('ajax_loader');
	updatePageHeader('Registration','to the famous bike rental service');
	$('main_content').innerHTML = '<form id="rendered_form_registered" style="margin: -24px -20px -38px -20px;">' + $('form_registered').innerHTML + '</form>';
	hideLoader('ajax_loader');
	
	
}
function form_registered(event){
	if (event) {	// may be called without any event
		Event.stop(event);
	}
	showLoader('ajax_loader');
	AjaxRequest('/ajax/Registration/', {
			method:'post',
			parameters: $('rendered_form_registered').serialize(true),
			onSuccess: function (response) {
				var obj = alertManagerGetAjaxResponse(response);
				hideLoader('ajax_loader');
				if(obj.success != undefined){
					alreadyLoggedIn(obj);
					loadBikeInfo();
				}
			},
			onFailure: function () {
				hideLoader('ajax_loader');
				alertRender('failure', "Connection problems.");
			}
		});
}

/*

ADMIN Invoice 

*/

function loadInvoice(){
	updatePageHeader('Administration','Manage your Invoices');
	
	if (event) {	// may be called without any event
		//Event.stop(event);
	}
	showLoader('ajax_loader');
	AjaxRequest('/ajax/Invoice/list', {
		method:'post',
		//parameters: $('frmFilterInvoice').serialize(true),
		onSuccess: loadInvoiceSuccess,
		onFailure: function () {
			$('main_content').update('AJAX Error');
			hideLoader('ajax_loader');
		}
	});
	return false;
}

function loadInvoiceSuccess(response){
	var obj = alertManagerGetAjaxResponse(response);
	
	var visualData = parseInvoiceList(obj);
	// Build table body = rows
	var body = '';
	var templateBody = new Template($('template_row_invoice').value);
	for (var i=0; i< visualData.length; i++) {
		body += templateBody.evaluate(visualData[i]);
	}

	// Build whole table
	var templateTable = new Template($('template_table_invoice').value);
	var tableHTML = templateTable.evaluate({ rows: body });
	$('main_content').update ( tableHTML );
	
	hideLoader('ajax_loader');
}

function parseInvoiceList(obj){
	var rtn = new Array();
	for(var i=0; i < obj.invoices.length; i++){
		var row =  new Object();
		row = obj.invoices[i];
		if(row.CustomerId > 0){
			row.customername = obj.customers[row.CustomerId].name;
		}
		else{
			row.customername = "error";
		}
		row.bikename = obj.bikes[row.BikeId].name;
		row.bikecatname = obj.bikeCats[row.BikeCatId].name;
		row.startDate = new Date(row.rent_start);
		row.start = formatDate(row.rent_start);
		
		if(row.rent_end != undefined){
			row.endDate = new Date(row.rent_end);
			row.end = formatDate(row.rent_end);
			row.duration = ((row.endDate.getTime()-row.startDate.getTime()) /(1000*60)).toFixed(2);
			if(row.saldo > 0){
				row.amount = (row.saldo/100).toFixed(2);
			}
			else{
				row.amount = "-";
			}
		}
		else{
			row.end = "open";
			row.duration = "-";
			row.amount = "-";
		}		
		rtn.push(row)
	}
	return rtn;
}

function formatDate(t){
	//alert(t);
	datetime = new Date(t);
	var str = "";
	str += datetime.getDate();
	str += ".";
	str += datetime.getMonth();
	str += ".";
	str += datetime.getFullYear();
	str += " ";
	str += datetime.getHours();
	str += ":";
	str += datetime.getMinutes();
	str += ":";
	str += datetime.getSeconds();
	return str;
}

function loadInvoiceInfo(invoiceId){
	showLoader('ajax_loader');
	AjaxRequest('/ajax/Invoice/info', {
		method:'post',
		parameters: {'txtInvoiceId': invoiceId},
		onSuccess: function () {
			hideLoader('ajax_loader');
		},
		onFailure: function () {
			$('main_content').update('AJAX Error');
			hideLoader('ajax_loader');
		}
	});
}
/*

rent 

*/

function rentStart(bikeId){
	showLoader('ajax_loader');
	AjaxRequest('/ajax/Rent/start', {
		method:'post',
		parameters: {'txtBikeId': bikeId},
		onSuccess: function () {
			hideLoader('ajax_loader');
		},
		onFailure: function () {
			$('main_content').update('AJAX Error');
			hideLoader('ajax_loader');
		}
	});
}


function rentEnd(){
	showLoader('ajax_loader');
	AjaxRequest('/ajax/Rent/end', {
		method:'post',
		//parameters: {'txtBikeId': bikeId},
		onSuccess: function () {
			hideLoader('ajax_loader');
		},
		onFailure: function () {
			$('main_content').update('AJAX Error');
			hideLoader('ajax_loader');
		}
	});
}

/*

 Stats Funktions

*/

function loadStats(){
	updatePageHeader('Statistics','');
	
	if (event) {	// may be called without any event
		//Event.stop(event);
	}
	$('main_content').innerHTML = "";
	showLoader('ajax_loader');
	loadStatsHelper('topFiveBiks','The five most popular bikes');
	loadStatsHelper('topFiveCustomers','The five most active customer');
	loadStatsHelper('topFiveCustomersMony','The five with the highest sales customer');
	loadStatsHelper('bikeCat','The most used bike category');
	
	return false;
}

function loadStatsHelper(name, titel){
	AjaxRequest('/ajax/Statistic/' + name, {
		method:'post',
		//parameters: $('frmFilterInvoice').serialize(true),
		onSuccess: function(response){
			loadStatsSuccess(response, titel);
		},
		onFailure: function () {
			$('main_content').update('AJAX Error');
			hideLoader('ajax_loader');
		}
	});
}

function loadStatsSuccess(response, titel){
	var obj = alertManagerGetAjaxResponse(response);
	obj.titel = titel;
	
	// Build whole table
	var templateTable = new Template("<div style='float:left;margin: 20px;'><h3>#{titel}<h3> <img src='#{img_src}'></div>");
	var tableHTML = templateTable.evaluate(obj);
	$('main_content').innerHTML += tableHTML;

	hideLoader('ajax_loader');
}
