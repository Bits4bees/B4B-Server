<template>
  <footer class="footer">
    <div class="container-fluid">
      <ul class="nav">
        <li class="nav-item">
          <a
            href="https://www.bits4bees.co/"
            target="_blank"
            rel="noopener"
            class="nav-link"
          >
            www.bits4bees.co/
          </a>
        </li>
        <li class="nav-item">
          <a
            href="https://www.bits4bees.co/about-us"
            target="_blank"
            rel="noopener"
            class="nav-link"
          >
            About Us
          </a>
        </li>
        <li class="nav-item">
          <a
            href="https://www.bits4bees.co/blog"
            target="_blank"
            rel="noopener"
            class="nav-link"
          >
            Blog
          </a>
        </li>
      </ul>
      <div class="copyright">
        &copy; {{ year }}, made with <i class="tim-icons icon-heart-2"></i>
        
        <!-- <a
          href="https://www.bits4bees.co/"
          target="_blank"
          rel="noopener"
          >IoTicos</a
        > -->
        <!-- for a better web. -->
      </div>
    </div>
  </footer>
</template>
<script>
export default {
  data() {
    return {
      year: new Date().getFullYear()
    };
  }
};
</script>
<style></style>
