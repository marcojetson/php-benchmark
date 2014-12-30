<?php

function in_array_b($needle, $haystack)
{
    $low = 0;
    $high = sizeof($haystack) - 1;
    while ($low <= $high) {
        $mid = floor(($high + $low) / 2);
        if ($haystack[$mid] > $needle) {
            $high = $mid - 1;
        } else if ($haystack[$mid] < $needle) {
            $low = $mid + 1;
        } else {
            return true;
        }
    }
    return false;
}

function in_array_l($needle, $haystack)
{
    for ($i = 0; $i < sizeof($haystack); $i++) {
        if ($haystack[$i] == $needle) {
            return true;
        }
    }
    return false;
}

$nombres = [
    'ana',
    'analia',
    'ernesto',
    'hector',
    'iliana',
    'lucia',
    'marco',
    'natalia',
    'omar',
    'ramon',
];

$bm1 = bm(function () use ($nombres) {
    in_array_b('omar', $nombres);
});

$bm2 = bm(function () use ($nombres) {
    in_array_l('omar', $nombres);
});

bm_write(function () use ($nombres) {
    in_array_l('omar', $nombres);
});

bm_writeln(function () use ($nombres) {
    in_array_l('omar', $nombres);
});