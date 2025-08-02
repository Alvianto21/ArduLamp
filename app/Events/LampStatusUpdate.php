<?php

namespace App\Events;

use Illuminate\Broadcasting\InteractsWithSockets;
use Illuminate\Foundation\Events\Dispatchable;
use Illuminate\Queue\SerializesModels;

class LampStatusUpdate
{
    use Dispatchable, InteractsWithSockets, SerializesModels;

    /**
     * Set new lamp status.
     *
     * @var string
     */
    public $status;
    /**
     * Create a new event instance.
     * 
     * @param string $status
     * @return void
     */
    public function __construct(String $status)
    {
        $this->status = $status;
    }

}
