<?
$output = exec('./cpp/fresh ./cpp/final.net 0 0',$op,$ret_val);
?>
<!DOCTYPE html>
<head>
  <meta charset="utf-8">
  <title>S.E.A.N.N. - MAKEFRESH</title>
  <link href="css/bootstrap.min.css" rel="stylesheet" media="screen">
  <link href="css/seann.css" rel="stylesheet" media="screen">
</head>
<body>
    <div class="container-fluid">

        <div class="well pagination-centered">
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
        </div>
    </div>
</body>