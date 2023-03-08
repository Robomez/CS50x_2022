let photoNum = 1;

document.addEventListener('DOMContentLoaded', function() {
    document.querySelector('#btnLeft').addEventListener('click', function() {
        if (photoNum == 1)
        {
            photoNum = 5;
        }
        else
        {
            photoNum -= 1;
        }
        document.querySelector('#catImage').innerHTML = "<img src='pictures/" + photoNum + ".jpg'>";
    });

    document.querySelector("#btnRight").addEventListener('click', function() {
        if (photoNum == 5)
        {
            photoNum = 1;
        }
        else
        {
            photoNum += 1;
        }
        document.querySelector('#catImage').innerHTML = "<img src='pictures/" + photoNum + ".jpg'>";
    });
});
