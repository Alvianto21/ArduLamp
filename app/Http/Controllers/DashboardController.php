<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Events\LampStatusUpdate;
use Illuminate\Support\Facades\Storage;
use Illuminate\Support\Facades\Log;

class DashboardController extends Controller
{
    public function index() {
         // Read the lamp status form file
        $status = Storage::disk('local')->get('lamp_status.txt');

        // Return to view
        return view('gate.dashboard', [
            'title' => 'Dashboard Page',
            'lampStatus' => $status === '1' ? 'ON' : 'OFF'
        ]);
    }

    public function saveStatus(Request $request) {
        // Log::info('Request recevied, validating ...', ['data' => $request->all()]);
        // Validate the request
        $request->validate([
            'status' => 'required|in:ON,OFF'
        ]);
        // Log::info('Validation passed');

        // Trigger the event to update the lamp status
        LampStatusUpdate::dispatch($request->input('status'));
        // Log::info('Lamp status updated by event');

        // Get new data
        $status = Storage::disk('local')->get('lamp_status.txt');
        // Log::info('Return to view', ['status' => $status]);

        // Return to view
        return redirect()->route('dashboard')->with('status', 'Lamp status changed to ' . ($status === '1' ? 'ON' : 'OFF'));
    }
}
