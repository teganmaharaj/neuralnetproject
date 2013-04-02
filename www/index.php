<!DOCTYPE html>
<head>
  <meta charset="utf-8">
  <title>S.E.A.N.N.</title>
  <link href="css/bootstrap.min.css" rel="stylesheet" media="screen">
  <style type="text/css">
      body {
        padding-top: 40px;
        padding-bottom: 40px;
        background-color: #FFF;
      }
  </style>
  <link rel="stylesheet" href="build/jquery.signaturepad.css">
  <!--[if lt IE 9]><script src="../build/flashcanvas.js"></script><![endif]-->
  <script src="http://code.jquery.com/jquery-latest.js"></script>
</head>
<body>

  <div class="container-fluid">
    <center><h1>S.E.A.N.N.</h1></center>

    <div class="form">
      <center>
      <form method="post" action="submit.php" class="sigPad">
        <canvas class="pad img-polaroid" width="100" height="150"></canvas>
        <input type="hidden" name="output" class="output">        
        <div class="btn-group">
          <button class="btn clearButton" href="#clear"><i class="icon-remove"></i> Clear</button>
          <button type="submit" class="btn btn-primary"><i class="icon-ok icon-white"></i> Submit</button>
        </div>
        </center>
      </form>
    </div>

    <div class="well">
      <p>
        An artificial neural network is a set of nodes with connections between them that each have a "weight", or cost to traverse the connection. To train the neural net, you give it some kind of input (like a drawing of a number), and if it gives the correct output (if it correctly identifies the number), you reward all the connection-paths that brought it to that output (you reduce the cost of traversing those connections later). If the neural network gives an incorrect output, you punish all the connection-paths leading to that output (increase the cost of going along that path). After doing this many times, the neural network will have sets of low-cost paths that make it more likely to reach correct outputs.
      </p>
      <p>
        To train the neural net, draw a number in the training field, tell it what number it is, and press train.
      </p>
      <p>
        To ask the neural net to identify a number, draw a number in the test     field, and press identify.
      </p>
      <p>Have fun!</p>
    </div>

    <div class="well">
      <ol>
        <li><div class="progress"><div class="bar" style="width: 60%;"></div></div></li>
        <li><div class="progress"><div class="bar" style="width: 40%;"></div></div></li>
        <li><div class="progress"><div class="bar" style="width: 30%;"></div></div></li>
        <li><div class="progress"><div class="bar" style="width: 70%;"></div></div></li>
        <li><div class="progress"><div class="bar" style="width: 45%;"></div></div></li>
        <li><div class="progress"><div class="bar" style="width: 10%;"></div></div></li>
        <li><div class="progress"><div class="bar" style="width: 20%;"></div></div></li>
        <li><div class="progress"><div class="bar" style="width: 80%;"></div></div></li>
        <li><div class="progress"><div class="bar" style="width: 50%;"></div></div></li>
        <li><div class="progress"><div class="bar" style="width: 150%;"></div></div></li>
      </ol>
    </div>
  </div>

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
