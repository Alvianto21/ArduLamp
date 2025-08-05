<x-homes.layout>
    <x-slot:title>{{ $title }}</x-slot:title>

    <p class="fs-5 col-md-8">Welcome to dashboard.</p>
    <p class="fs-5 col-md-8">This button is used to control lamp.</p>
    <div class="d-flex gap-2 justify-content-center py-5">
        <button type="button" onclick="toggleStatus()" class="btn btn-primary" id="lamp" data-status="OFF"></button>
    </div>

    // FixMe gunakan form atau button link untuk proses ini dan gunakan routes helper
    // xxx osional gunakan controller untuk mengelola rute
    @push('scripts')
        <!-- Adisional Script -->
        <script src="{{ asset('js/evenButtons.js') }}"></script>
    @endpush
</x-homes.layout>
