<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <meta name="description" content="IoT lamp control using arduino uno r3 and laravel 11">
    <meta name="author" content="Vinsensius Alvianto Mardi Utomo">

    <!-- Bootstrapt Css -->
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.7/dist/css/bootstrap.min.css" integrity="sha384-LN+7fdVzj6u52u30Kp6M/trliBMCMKTyK833zpbD+pXdCLuTusPj697FH4R/5mcr" crossorigin="anonymous">

    <!-- Bootstrap Icons -->
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap-icons@1.13.1/font/bootstrap-icons.min.css">

    <!-- Vite -->
    @vite(['resources/css/app.css', 'resources/js/app.js'])

    <title>Ardulamp | {{ $title ?? 'Default title' }}</title>
</head>

<body>
    @guest
    <!-- Navbar -->
    <x-homes.navbar></x-homes.navbar>
        
    @endguest

    @auth
        <!-- Side Bar -->
        <x-homes.sidebar></x-homes.sidebar>
    @endauth
    <div class="col-lg-8 mx-auto p-4 py-md-5">
        <!-- Header -->
        <x-homes.header>{{ $title ?? 'Default title' }}</x-homes.header>


        <!-- Main Content -->
        <main>
            {{ $slot }}
        </main>
    </div>

    <!-- Bootsrap Js -->
    <script src="https://cdn.jsdelivr.net/npm/@popperjs/core@2.11.8/dist/umd/popper.min.js" integrity="sha384-I7E8VVD/ismYTF4hNIPjVp/Zjvgyol6VFvRkX/vR+Vc4jQkC+hVqc2pM8ODewa9r" crossorigin="anonymous"></script>

    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.7/dist/js/bootstrap.min.js" integrity="sha384-7qAoOXltbVP82dhxHAUje59V5r2YsVfBafyUDxEdApLPmcdhBPg1DKg1ERo0BZlK" crossorigin="anonymous"></script>

    @stack('scripts')
</body>

</html>
