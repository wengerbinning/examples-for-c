
let loginForm = document.forms["login"];

loginForm.addEventListener("submit", (e) => {
	e.preventDefault();

    let form = e.srcElement;
	let username = form.elements.namedItem("username");
	let password = form.elements.namedItem("password");

	console.log(username.value);
	console.log(password.value);

    // const xhttp = new XMLHttpRequest();
    // xhttp.open("GET", "ajax_info.txt", true);
    // xhttp.send();   
    
    // $.ajax({
    //     type: "POST",
    //     url: "https://127.0.0.1",
    //     data: form.serialize(), // serializes the form's elements.
    //     success: function(data)
    //     {
    //       alert(    ); // show response from the php script.
    //     }
    // });



    fetch('/login', {
        method: "POST",
        body: form,
        // headers: {
        //     'Accept': 'application/json',
        // }
    }).then(response => {
        console.log(response);
    }).catch(error => {
        console.log(error);
    });
});