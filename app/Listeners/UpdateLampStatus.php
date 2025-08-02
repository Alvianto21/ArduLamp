<?php

namespace App\Listeners;

use App\Events\LampStatusUpdate;
use Illuminate\Support\Facades\Log;
use Illuminate\Support\Facades\Storage;

class UpdateLampStatus
{
    /**
     * Create the event listener.
     */
    public function __construct()
    {
        //
    }

    /**
     * Handle the event.
     * 
     * @param LampStatusUpdate $event
     * @return void
     */
    public function handle(LampStatusUpdate $event): void
    {
        // Set new status and convert it to '1' for ON or '0' for OFF
        $newStatus = $event->status === 'ON' ? '1' : '0';

        // Write the new status to the file
        Storage::disk('local')->put('lamp_status.txt', $newStatus);
        Log::info('Lamp status updated', ['new_status' => $newStatus]);
    }
}
