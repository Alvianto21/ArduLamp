<x-homes.layout>
    <x-slot:title>{{ $title }}</x-slot:title>

    <p class="fs-5 col-md-8">Welcome to dashboard.</p>
    <p class="fs-5 col-md-8">This button is used to control lamp.</p>
    <div class="d-flex gap-2 justify-content-center py-5">
        <a href="{{ route('dashboard.lamp', ['status' => $lampStatus === 'ON' ? 'OFF' : 'ON']) }}" type="button" class="btn btn-primary">Lamp {{ $lampStatus }}</a>
    </div>

    <!-- FixMe gunakan form atau button link untuk proses ini dan gunakan routes helper
    xxx osional gunakan controller untuk mengelola rute
    xxx posible upgrade, gunakan livewire 3 untuk fungsi baru dan service layer untuk pelaporan status -->
</x-homes.layout>
