<?php

namespace App\Listeners;

use PhpMqtt\Client\ConnectionSettings;
use PhpMqtt\Client\MqttClient;
use App\Events\LampStatusUpdate;
use Illuminate\Support\Facades\Log;
use Illuminate\Queue\InteractsWithQueue;
use Illuminate\Contracts\Queue\ShouldQueue;

class PublishLampStatus
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
     */
    public function handle(LampStatusUpdate $event): void
    {
        // Set new status and convert it to '1' for ON or '0' for OFF
        $newStatus = $event->status;

        // Setup MQTT connection
        $host = config('mqtt-client.connections.default.host');
        $port = config('mqtt-client.connections.default.port');
        $client_id = config('mqtt-client.connections.default.client_id');
        $mqtt = new MqttClient($host, $port, $client_id);
        $idCard = (new ConnectionSettings)
            ->setUsername(env('MQTT_AUTH_USERNAME'))
            ->setPassword(env('MQTT_AUTH_PASSWORD'));

        // Open connection
        try {
            $mqtt->connect($idCard, true);
            // Log::info("MQTT connection established", [
            //     'host' => $host,
            //     'port' => $port,
            //     'cliebt_id' => $client_id
            // ]);

            // Publish the message
            $mqtt->publish('lamp/status', $newStatus);
            // Log::info("data sending", ['data' => $newStatus]);

            // close the MQTT connection
            $mqtt->disconnect();
        } catch (\Exception $e) {
            // Log::error("MQTT connection failed", [
            //     'error' => $e->getMessage(),
            //     'host' => $host,
            //     'port' => $port,
            //     'cliebt_id' => $client_id
            // ]);
        }
    }
}
