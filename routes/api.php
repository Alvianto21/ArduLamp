<?php

use App\Http\Controllers\api\ControlLampController;
use Illuminate\Http\Request;
use Illuminate\Support\Facades\Route;

// Route::get('/user', function (Request $request) {
//     return $request->user();
// })->middleware('auth:sanctum');

Route::get('/lamp-status', [ControlLampController::class, 'getLampStatus'])->name('lamp.status');

route::post('/lamp-status', [ControlLampController::class, 'changeLampStatus'])->name('lamp.changeStatus');