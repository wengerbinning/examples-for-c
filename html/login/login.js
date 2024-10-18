
let loginForm = document.forms["login"];

loginForm.addEventListener("submit", (e) => {
    e.preventDefault();

    const url = "/api/login";

    let form = e.srcElement;
    let username = form.elements.namedItem("username");
    let password = form.elements.namedItem("password");
    const data = {
        username: username.value,
        password: password.value,
    };

    console.log(username.value);
    console.log(password.value);


    
    $.ajax({
        type: "POST",
        url: url,
        data: JSON.stringify(data),
        
        // headers: headers,
        // crossDomain: true, // FIXME - CORS
        // beforeSend: function(request) {
        //     request.setRequestHeader("Access-Control-Allow-Method", "GET, POST, OPTIONS");
        //     request.setRequestHeader("Access-Control-Allow-Origin", "*");
        // },
      }).done(function (data) {
        console.log(data);
      });
});