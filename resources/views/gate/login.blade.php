<x-homes.layout>
    <x-slot:title>{{ $title }}</x-slot:title>

    <!-- Session Status -->
    <x-auth-session-status class="mb-4" :status="session('status')" />

    <!-- Login Form -->
    <div class="col-md-8">
        <form method="POST" action="{{ route('login') }}">
            @csrf
            <div class="mb-3">
                <label for="email1" class="form-label">Email address</label>
                <input type="email" class="form-control" name="email" id="email" value="{{ old('email') }}" required autofocus>
                <x-input-error :messages="$errors->get('email')" class="mt-2" />
            </div>
            <div class="mb-3">
                <label for="Password1" class="form-label">Password</label>
                <input type="password" class="form-control" name="password" id="password" required autocomplete="current-password">
				<x-input-error :messages="$errors->get('password')" class="mt-2" />
            </div>
            <button type="submit" class="btn btn-primary">Submit</button>
        </form>
    </div>
</x-homes.layout>
