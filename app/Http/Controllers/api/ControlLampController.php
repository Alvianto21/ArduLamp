<?php

namespace App\Http\Controllers\api;

use App\Events\LampStatusUpdate;
use Illuminate\Http\Request;
use App\Http\Controllers\Controller;
use Illuminate\Support\Facades\Log;
use Illuminate\Support\Facades\Storage;

class ControlLampController extends Controller
{
    /** 
     * Get the status of the lamp.
     * Connect this to your arduino
     */
    public function getLampStatus()
    {
        // Read the lamp status form file
        $status = Storage::disk('local')->get('lamp_status.txt');
        // Log::info('Lamp status retrieved', ['status' => $status]);

        // Return the status as a JSON response and convert it to boolean
        return response()->json([
            'status' => $status === '1' ? 'ON' : 'OFF'
        ], 200);
    }

    /**
     * Send a request to change the lamp status.
     */
    public function changeLampStatus(Request $request)
    {
        // Validate the input
        // input most be either 'ON' or 'OFF'
        // Log::info('Changing lamp status', ['status' => $request->input('status')]);

        $request->validate([
            'status' => 'required|in:ON,OFF'
        ]);
        // Log::info('Validation passed');

        // Trigger the event to update the lamp status
        LampStatusUpdate::dispatch($request->input('status'));
        // Log::info('Lamp status updated by event');

        // Get the updated data
        $update = Storage::disk('local')->get('lamp_status.txt');

        // Return response
        return response()->json([
            'message' => 'Lamp status change to ' . $request->input('status'),
            'status' => $update === '1' ? 'ON' : 'OFF'
        ], 200);
    }
}
