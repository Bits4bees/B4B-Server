<template>
  <div v-if="$store.state.devices.length > 0">
    <div class="row">
      <v-container class="chart-container">
        <div class="col-6">
          <line-chart
            :chart-options="chartOptions"
            :chart-data="chartTempInt"
            chart-id="tempInterna"
          />
        </div>
      </v-container>

      <v-container class="chart-container">
        <div class="col-6">
          <line-chart
            :chart-options="chartOptions"
            :chart-data="chartTempExt"
            chart-id="tempExterna"
          />
        </div>
      </v-container>
    </div>

    <div class="row" v-if="$store.state.devices.length > 0">
      <v-container class="chart-container">
        <div class="col-6">
          <line-chart
            :chart-options="chartOptions"
            :chart-data="chartHumInt"
            chart-id="humInterna"
          />
        </div>
      </v-container>

      <v-container class="chart-container">
        <div class="col-6">
          <line-chart
            :chart-options="chartOptions"
            :chart-data="chartHumExt"
            chart-id="humExterna"
          />
        </div>
      </v-container>
    </div>
  </div>

  <div v-else>
    Select a Device
  </div>
</template>

<script>
export default {
  middleware: "authenticated",
  name: "Details",
  data() {
    return {
      chartOptions: {
        scales: {
          yAxes: [
            {
              ticks: {
                beginAtZero: true
              }
            }
          ]
        },
        responsive: true,
        maintainAspectRatio: true
      },
      chartTempExt: {
        labels: ["January", "February", "March"],
        datasets: [
          {
            label: "Temperatura externa",
            data: [65, 59, 80, 81, 56, 55, 40],
            fill: false,
            borderColor: "rgb(75, 192, 192)",
            tension: 0.1
          }
        ]
      },
      chartTempInt: {
        labels: ["January", "February", "March"],
        datasets: [
          {
            label: "Temperatura interna",
            data: [65, 59, 80, 81, 56, 55, 40],
            fill: false,
            borderColor: "rgb(75, 192, 192)",
            tension: 0.1
          }
        ]
      },
      chartHumExt: {
        labels: ["January", "February", "March"],
        datasets: [
          {
            label: "Humedad externa",
            data: [65, 59, 80, 81, 56, 55, 40],
            fill: false,
            borderColor: "rgb(75, 192, 192)",
            tension: 0.1
          }
        ]
      },
      chartHumInt: {
        labels: ["January", "February", "March"],
        datasets: [
          {
            label: "Humedad externa",
            data: [65, 59, 80, 81, 56, 55, 40],
            fill: false,
            borderColor: "rgb(75, 192, 192)",
            tension: 0.1
          }
        ]
      }
    };
  },

  mounted() {},

  methods: {
    fixWidget(widget) {
      var widgetCopy = JSON.parse(JSON.stringify(widget));
      widgetCopy.selectedDevice.dId = this.$store.state.selectedDevice.dId;
      widgetCopy.selectedDevice.name = this.$store.state.selectedDevice.name;
      widgetCopy.userId = this.$store.state.selectedDevice.userId;

      if (widget.widget == "numberchart") {
        widgetCopy.demo = false;
      }

      return widgetCopy;
    }
  }
};
</script>
