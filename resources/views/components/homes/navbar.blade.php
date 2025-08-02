<ul class="nav nav-tabs">
    <li class="nav-item">
        <x-homes.navlink href="/" :active="request()->is('/')">Home</x-homes.navlink>
    </li>
    @guest
        <li class="nav-item">
            <x-homes.navlink href="/login" :active="request()->is('login')">Login</x-homes.navlink>
        </li>
    @endguest
    @auth
        <li class="nav-item">
            <x-homes.navlink href="/dashboard" :active="request()->is('dashboard')">Dashboard</x-homes.navlink>
        </li>
    @endauth
</ul>
