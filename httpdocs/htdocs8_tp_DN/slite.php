<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <meta name="description" content="">
    <meta name="author" content="">
    <link href="assets/fonts/myfont.css" rel="stylesheet">
    <title>vote box</title>
    <link rel="icon" type="image/x-icon" href="assets/images/3DSV.png" />
    <link href="vendor/bootstrap/css/bootstrap.min.css" rel="stylesheet">
    <link rel="stylesheet" href="assets/css/fontawesome.css">
    <link rel="stylesheet" href="assets/css/templatemo-grad-school.css">
    <link rel="stylesheet" href="assets/css/owl.css">
    <link rel="stylesheet" href="assets/css/lightbox.css">
</head>

<body>
    <header class="main-header clearfix" role="header">
        <div class="logo" style="display: flex;">
            <img id="logo" src="assets/images/logo.png" alt="spkt" style="height: 60px; margin: 10px; margin-right: 20px;">
            <a href="#" ><em></em></a>
        </div>  
        <nav id="menu" class="main-nav" role="navigation">
        </nav>
    </header>
    <section class="section main-banner" id="top" data-section="section1">
        <img id="bg-video" src="assets/images/ba.png" alt="background">
        <div class="video-overlay header-text">
            <div class="caption" style="display: flex; flex-direction: column;">
     
                <div style="margin-bottom: 5%;">
                    <h2 id="changeRule">tổng số phiếu: <em ><?php include 'showSumx2.php'?></em> phiếu</h2>
                </div>
                <div style="display: flex; flex-direction: row;">
                    <div style="flex: 1;">
                        <h2  style="font-size: 40px; ">Tổng số phiếu bầu đại biểu chính thức dự Đại hội Đoàn toàn quốc lần thứ xii: <em><?php include 'showSum.php'?></em> phiếu</h2>
                    </div>
                    <div style=" border-left-style: solid; border-color: #f5a425; border-width: 5px; margin: 5%;">  
                    </div>
                    <div style="flex: 1;">
                        <h2 style="font-size: 40px; " >Tổng số phiếu bầu đại biểu dự khuyết dự Đại hội Đoàn toàn quốc lần thứ xii: <em><?php include 'showSum.php'?></em> phiếu</h2>
                        
                    </div>

                </div>
            </div>
        </div>
    </section>
    <script>
        const logo = document.getElementById("logo");
        document.getElementById("changeRule").addEventListener("click", changeRule);
        function changeRule() {
            let paswd = prompt("nhập mật khẩu");
            if (paswd == "0120") {
                $.get("setRule.php", function (data) {
                    if (data == "on") {
                        logo.src = "assets/images/logo.png";
                        alert("đã bật chế độ chuyển slite");
                    } else if (data == "off") {
                        logo.src = "assets/images/logox.png";
                        alert("đã tắt chế độ chuyển slite");
                    }
                });
            } else {
                alert("Bạn đã nhập mật khẩu sai!!!")
            }
        }
    </script>
    <script src="assets/js/isotope.min.js"></script>
    <script src="assets/js/owl-carousel.js"></script>
    <script src="assets/js/lightbox.js"></script>
    <script src="assets/js/tabs.js"></script>
    <script src="assets/js/video.js"></script>
    <script src="assets/js/slick-slider.js"></script>
</body>

</html>