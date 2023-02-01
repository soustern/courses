document.addEventListener('DOMContentLoaded', function () {
    // When hovered, logo middle receives a glow
    let glow = document.querySelectorAll('.logo_middle')
    let hover = document.querySelector('.logo_wrap');

    hover.addEventListener('mouseenter', function () {
        glow[0].classList.add('glow');
        glow[1].classList.add('glow');
    });

    hover.addEventListener('mouseleave', function () {
        glow[0].classList.remove('glow');
        glow[1].classList.remove('glow');
    });

});