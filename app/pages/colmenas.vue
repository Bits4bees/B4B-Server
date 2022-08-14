<template>

  <div class="d-flex flex-wrap" v-if="$store.state.devices.length > 0">

    <div v-for="(device, dindex) in $store.state.devices"  :key="dindex">
      <div v-for="(widget, index) in device.template.widgets" :key="index"
        :class="[widget.column]">
        <colmenachart v-if="widget.widget == 'colmenachart'" :config="fixWidget(widget, device)"></colmenachart>
        <Rtnumberchart v-if="widget.widget == 'numberchart'" :config="fixWidget(widget, device)"></Rtnumberchart>

        <Rtfttchart v-if="widget.widget == 'fttchart'" :config="fixWidget(widget, device)"></Rtfttchart>

        <Iotswitch v-if="widget.widget == 'switch'" :config="fixWidget(widget, device)"></Iotswitch>

        <Iotbutton v-if="widget.widget == 'button'" :config="fixWidget(widget, device)"></Iotbutton>

        <Iotindicator v-if="widget.widget == 'indicator'" :config="fixWidget(widget, device)"></Iotindicator>
      </div>
    </div>

  </div>

  <div v-else>
    Select a Device
  </div>

</template>
<script>

export default {
  middleware: 'authenticated',
  name: 'Colmenas',
  data() {
    return {


    }
  },

  mounted() {


  },

  methods: {

    fixWidget(widget, device) {
      var widgetCopy = JSON.parse(JSON.stringify(widget));
      widgetCopy.selectedDevice.dId = device.dId;
      widgetCopy.selectedDevice.name = device.name;
      widgetCopy.userId = this.$store.state.selectedDevice.userId;
      if (widget.widget == "numberchart") {
        widgetCopy.demo = false;
      }

      widget.column = "col-12";
      widget.selectedDevice.dId = device.dId;
      widgetCopy.selectedDevice.values=device.values;
      widget.selectedDevice.values=device.values;


      return widgetCopy;
    }

  }

};
</script>