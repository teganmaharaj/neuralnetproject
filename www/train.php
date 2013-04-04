<!DOCTYPE html>
<head>
  <meta charset="utf-8">
  <title>S.E.A.N.N. - Training</title>
  <link href="css/bootstrap.min.css" rel="stylesheet" media="screen">
  <style type="text/css">
      body {
        padding-top: 40px;
        padding-bottom: 40px;
        background: url('img/grey.png');
      }
      .form {
        width:400px;
      }
      .btn-group {
        padding:10px;
      }
  </style>
  <link rel="stylesheet" href="build/jquery.signaturepad.css">
  <!--[if lt IE 9]><script src="../build/flashcanvas.js"></script><![endif]-->
  <script src="http://code.jquery.com/jquery-latest.js"></script>
</head>
<body>
  <center>
  <div class="form well">
    <center>
      <a class="btn btn-success" href="./"><i class="icon-home icon-white"></i> Home</a>
      <a class="btn btn-danger" href="./make_fresh.php"><i class="icon-repeat icon-white"></i> Make new brainfile!</a>
    </center>
    <form method="post" action="result.php" class="sigPad">
      <canvas class="pad img-polaroid" width="100" height="150"></canvas>
      <input type="hidden" name="output" class="output">
      <div class="btn-toolbar">
        <div class="btn-group">
          <button class="btn clearButton" href="#clear"><i class="icon-remove"></i> Clear</button>
        </div>
        <div class="btn-group">
          <button type="submit" class="btn btn-primary" name="number" value="0">0</button>
          <button type="submit" class="btn btn-primary" name="number" value="1">1</button>
          <button type="submit" class="btn btn-primary" name="number" value="2">2</button>
          <button type="submit" class="btn btn-primary" name="number" value="3">3</button>
          <button type="submit" class="btn btn-primary" name="number" value="4">4</button>
          <button type="submit" class="btn btn-primary" name="number" value="5">5</button>
          <button type="submit" class="btn btn-primary" name="number" value="6">6</button>
          <button type="submit" class="btn btn-primary" name="number" value="7">7</button>
          <button type="submit" class="btn btn-primary" name="number" value="8">8</button>
          <button type="submit" class="btn btn-primary" name="number" value="9">9</button>
        </div>
      </div>
    </form>
  </div>
  </center>

  <script src="build/jquery.signaturepad.min.js"></script>
  <script>
    $(document).ready(function() {
      var options = {
        penColour : '#000',
        penCap : 'round',
        lineColour : '#FFF',
        lineTop : 200,
        lineWidth : 0,
        penWidth : 10,
        drawOnly : true
      };
    
    $('.sigPad').signaturePad(options);
      $('.sigPad').signaturePad(options);
    });
  </script>
  <script src="js/bootstrap.min.js"></script>
  <script src="build/json2.min.js"></script>
</body>