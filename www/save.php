<?php

require_once 'genImage.php';

$img = sigJsonToImage(file_get_contents($_POST['output']));

$date = new DateTime();
$filename = $date->format('U = Y-m-d-H-i-s')+'x'+$_POST['value'];

// Output to browser
header('Content-Type: image/png');
imagepng($img);

// Save to file
imagepng($img, $filename+'.png');

for ($y=0; $y < 150; $y++) {
	for ($x=0; $x < 100; $x++) {
			if (imagecolorat($img, $x, $y) == 0){
				print '1';
			} else {
				print '0';
			}
	}
	print "\n";
}

$string = '010010101001010010010010111010101101001010100100100101011101011010010101010100101010010101001011101001';

//exec('neuralnet'+$_POST['value']+$string);



// Destroy the image in memory when complete
imagedestroy($img);
