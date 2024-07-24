
//Javacsript file for Header and Footer.


// Get the header / footer by query class select. Then create variable for both.
const mainHeader = document.querySelector('#main-header');
const mainFooter = document.querySelector('#footer-section');

// Header - Get content
mainHeader.innerHTML = `


<nav class="navbar">
<a href="home.html" class="active"><img src="images/motor-icon2.png"></a>
<a href="product.html" class="noHover">Products</a>
<a href="Aboutus.html" class="noHover">About Our Company</a>

<a href="contact-us.html" class="noHover">Contact Us</a>

<div class="dropdown">
    <input type="image" src="images/search-icon.png" onclick="myFunction()" id="searchbar" width="17" height="17">
    <div id="actualdropdown" class="dropdown-content">
        <form action="searchreceive.html" method="get"><input type="text" id="searchtext" name="search" placeholder="Search..."></form>
    </div>
</div>
</nav>
`;

/*<a href="#" class="right" class="noHover"><img src="images/search-icon.png" ></a>*/


//Function to toggle search bar..
function myFunction(){
    document.getElementById("actualdropdown").classList.toggle("show");

}



/*
//execute stickyHead function when user scrolls
window.onscroll = function() {stickHead()};

//hold header
var head = document.getElementById("main-header");

//Find offset pos of nav
var sticky = header.offsetTop;



function stickHead(){

    if(window.pageYOffset.sticky){
        head.classList.add("sticky");
    }
    else{
        head.classList.remove("sticky");
    }

}
*/

// include footer
// mainFooter.innerHTML = `
// <div class="footer">
//   <h2>Footer</h2>
// </div>
// `;


mainFooter.innerHTML = `

<footer class="footer-distributed">
    
    <div class="container">

        <p class="text-field">
            Motorola Incorporated is in accordance with the North America technology act of 1980.
        </p>

        <hr id="line">

        <div class="row">
    
            <div class="footer-col">
                <h3 class="headers">Products</h3>
                <ul> 
                    <li class="list-item"><a href="product.html" class="anchorfoot">Dynatac 8000x</a></li>
                    <li class="list-item">Speakers</li>
                    <li class="list-item">Home Phones</li>
                    <li class="list-item">Televisions</li>
                </ul>


            </div>
        
            <div class="footer-col">
                <h3 class="headers">Learn</h3>
                <ul> 
                    <li class="list-item">Product info</li>
                    <li class="list-item">New Technology</li>
                    <li class="list-item">Careers</li>
                    <li class="list-item">Training Program</li>
                </ul>

            </div>

            <div class="footer-col">
                <h3 class="headers">About Us</h3>
                <ul> 
                    <li class="list-item">How We Started</li>
                    <li class="list-item">Our History</li>
                    <li class="list-item">What To Buy</li>
                    <li class="list-item">Product Decision</li>
                </ul>

            </div>

            <div class="footer-col">
                <h3 class="headers">Legal</h3>
                <ul> 
                    <li class="list-item">Company Guidelines</li>
                    <li class="list-item">Return Policy</li>
                    <li class="list-item">Product Policy</li>
                    <li class="list-item">Patent Information</li>
                </ul>

            </div>

        </div>

        <hr id="line">
        <p class="text-field">
            Copyright &#169 Motorola Inc. All rights reserved.
        </p>
        <p id="bottom-text">
            If you are having trouble with your Motorola product. Please call Customer Service @ 1-800-788-7878.
        </p>
    </div>
  

</footer>
`;





// <header>
//   <nav>
//     <ul>
//       <li><a href="about.html">About</a></li>
//       <li><a href="work.html">Work</a></li>
//       <li><a href="contact.html">Contact</a></li>
//     </ul>
//   </nav>
// </header>

//document.body.appendChild(template.content);

