<?
$output = exec('./cpp/make fresh',$op,$ret_val);

?>
<!DOCTYPE html>
<head>
  <meta charset="utf-8">
  <title>S.E.A.N.N. - MAKEFRESH</title>
  <link href="css/bootstrap.min.css" rel="stylesheet" media="screen">
  <style type="text/css">
    body {
        padding-top: 40px;
        padding-bottom: 40px;
        background: url('img/grey.png');
    }
    .container-fluid {
        margin:0 20%;
    }
    dd {
        margin-left: 30px;
        margin-top: -20px;
    }
  </style>

  <script src="http://code.jquery.com/jquery-latest.js"></script>
</head>
<body>
    <div class="container-fluid">

        <div class="well">
            <center>
              <a class="btn btn-success" href="./"><i class="icon-home icon-white"></i> Home</a>
              <a class="btn btn-warning" href="./train.php"><i class="icon-pencil icon-white"></i> Train</a>
              <p>
              	<?
					if ($ret_val != 0) {
					  print "ERROR!</br>Returned: ".$ret_val."</br>Result: ".$result."</br>Var Dump: ";
					  var_dump(parse_str($output));
					}
              		echo print $output;

              	?>
          	  </p>
            </center>
        </div>
    </div>

  <script src="js/bootstrap.min.js"></script>
</body>