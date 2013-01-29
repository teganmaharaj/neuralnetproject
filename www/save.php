<?php

require_once 'genImage.php';

$img = sigJsonToImage(file_get_contents($_POST['output']));

// Save to file
imagepng($img, 'image.png');

// Output to browser
header('Content-Type: image/png');
imagepng($img);

// Destroy the image in memory when complete
imagedestroy($img);
