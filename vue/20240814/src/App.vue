//
<script setup>
import Index from './components/Index.vue' 
import WiKi from './components/WiKi.vue'
import About from './components/About.vue'
import NotFound from './components/NotFound.vue'

const routes = {
    '/': Index,
    '/wiki': WiKi,
    '/about': About
}

const currentPath = ref(windows.location.hash);

window.addEventListener('hashchange', () => {
	currentPath.value = windows.location.hash
})

const currentView = computed(() => {
	return routes[currentPath.value.slice(1) || '/'] || NotFound 	
})
</script>

//
<template>
  <header>
    <img alt="Vue logo" class="logo" src="./assets/logo.svg" width="125" height="125" />

  </header>

  <main>
	  <a href="#/wiki">WiKi</a>
	  <a href="#/about">About</a>
  </main>
</template>

//
<style scoped>
header {
  line-height: 1.5;
}

.logo {
  display: block;
  margin: 0 auto 2rem;
}

@media (min-width: 1024px) {
  header {
    display: flex;
    place-items: center;
    padding-right: calc(var(--section-gap) / 2);
  }

  .logo {
    margin: 0 2rem 0 0;
  }

  header .wrapper {
    display: flex;
    place-items: flex-start;
    flex-wrap: wrap;
  }
}
</style>
