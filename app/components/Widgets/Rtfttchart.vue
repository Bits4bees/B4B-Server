<template>
    <card type="chart">
        <!-- MAX HISTORY -->
        <template slot="header">
            <h5 class="card-category pull-right">{{getTimeAgo((nowTime - time) / 1000)}} ago </h5>       
            <h5 class="card-category">{{ config.selectedDevice.name }} - {{ config.variableFullName }}</h5>
            <h3 class="card-title">
                <i class="fa " :class="[config.icon, getIconColorClass()]" aria-hidden="true"
                    style="font-size: 30px;"></i>
                <span>{{value.toFixed(config.decimalPlaces)}} {{config.unit}}</span>
            </h3>
        </template>
        <div class="chart-area" style="height: 300px">
            <highchart style="height: 100%" v-if="isMounted" :options="chartOptions"/>
        </div>
    </card>
</template>


<script>        
    export default {
        name: 'rtfttpchart',
        props: ['config'],
        data() {
            return {
                receivedTime: 0,
                value: 0,
                time: Date.now(),
                nowTime: Date.now(),
                isMounted: false,
                topic: "",

                chartOptions: {
                    credits: {
                        enabled: false
                    },
                    chart: {
                        renderTo: 'container',
                        defaultSeriesType: 'line',
                        backgroundColor: 'rgba(0,0,0,0)',
                    },
                    title: {
                        text: ''
                    },
                    xAxis: {
                        type: 'datetime',
                        labels: {
                            style: {
                                color: '#d4d2d2'
                            }
                        }
                    },
                    yAxis: {
                        title: {
                            text: ''
                        },
                        labels: {
                            style: {
                                color: '#d4d2d2',
                                font: '11px Trebuchet MS, Verdana, sans-serif'
                            }
                        }
                    },

                    plotOptions: {
                        series: {
                            label: {
                                connectorAllowed: false,
                            },
                            pointStart: 2010
                        }
                    },
                    series: [{
                        name: '',
                        data: [],
                        color: "#e14eca"
                    },],
                    legend: {
                        itemStyle: {
                            color: '#d4d2d2'
                        }
                    },
                    responsive: {
                        rules: [{
                            condition: {
                                maxWidth: 500
                            },
                            chartOptions: {
                                legend: {
                                    layout: 'horizontal',
                                    align: 'center',
                                    verticalAlign: 'bottom'
                                }
                            }
                        }]
                    }
                },

            };
        },
        watch:  {
            config: {
                immediate: true,
                deep: true,
                handler() {
                    setTimeout(() => {
                        this.value = 0;

                        this.$nuxt.$off(this.topic + "/sdata");

                        this.topic = this.config.userId + '/' + this.config.selectedDevice.dId + '/' + this.config.variable;
                        this.$nuxt.$on(this.topic + "/sdata", this.procesReceivedData);

                        this.chartOptions.series[0].data = [];

                        this.getChartData();


                        this.chartOptions.series[0].name = this.config.variableFullName + " " + this.config.unit;
                        this.updateColorClass();
                        window.dispatchEvent(new Event('resize'));
                    }, 300);
                }
            }
        },
        mounted() {

            this.getNow();
            this.updateColorClass();

        },
        beforeDestroy() {
            this.$nuxt.$off(this.topic + "/sdata");
        },
        methods: {

            updateColorClass() {
                console.log("update" + this.config.class)

                var c = this.config.class;

                if (c == "success") {
                    this.chartOptions.series[0].color = "#00f2c3";
                }
                if (c == "primary") {
                    this.chartOptions.series[0].color = "#e14eca";
                }
                if (c == "warning") {
                    this.chartOptions.series[0].color = "#ff8d72";
                }
                if (c == "danger") {
                    this.chartOptions.series[0].color = "#fd5d93";
                }

                this.chartOptions.series[0].name = this.config.variableFullName + " " + this.config.unit;

            },

            async getChartData() {

                if (this.config.demo) {                   
                    // console.log("ESTAMOS AQUI.....");
                    // await fetch("./fttdata.txt")
                    //     .then(response => response.textson())
                    //     .then(data => console.log(data));
                    // let reader = new FileReader();
                    // reader.readAsText(fttdata.txt);

                    this.chartOptions.series[0].data =
                    [
                        [1,409],
                        [2,409],
                        [3,920],
                        [4,512],
                        [5,291],
                        [6,256],
                        [7,329],
                        [8,157],
                        [9,298],
                        [10,213],
                        [11,405],
                        [12,113],
                        [13,614],
                        [14,479],
                        [15,1905],
                        [16,3009],
                        [17,2381],
                        [18,2453],
                        [19,1545],
                        [20,646],
                        [21,681],
                        [22,1067],
                        [23,867],
                        [24,370],
                        [25,210],
                        [26,550],
                        [27,734],
                        [28,588],
                        [29,520],
                        [30,95],
                        [31,126],
                        [32,66],
                        [33,482],
                        [34,8610],
                        [35,11829],
                        [36,2186],
                        [37,679],
                        [38,1019],
                        [39,1137],
                        [40,386],
                        [41,562],
                        [42,648],
                        [43,474],
                        [44,577],
                        [45,348],
                        [46,302],
                        [47,265],
                        [48,277],
                        [49,340],
                        [50,1021],
                        [51,1410],
                        [52,308],
                        [53,1114],
                        [54,819],
                        [55,528],
                        [56,830],
                        [57,560],
                        [58,461],
                        [59,218],
                        [60,777],
                        [61,524],
                        [62,829],
                        [63,669],
                        [64,729],
                        [65,494],
                        [66,485],
                        [67,342],
                        [68,2556],
                        [69,14246],
                        [70,9919],
                        [71,422],
                        [72,436],
                        [73,163],
                        [74,559],
                        [75,564],
                        [76,129],
                        [77,518],
                        [78,434],
                        [79,170],
                        [80,135],
                        [81,295],
                        [82,762],
                        [83,672],
                        [84,656],
                        [85,1582],
                        [86,2938],
                        [87,2694],
                        [88,1117],
                        [89,734],
                        [90,926],
                        [91,1071],
                        [92,898],
                        [93,521],
                        [94,346],
                        [95,390],
                        [96,1180],
                        [97,846],
                        [98,1177],
                        [99,929],
                        [100,1722],
                        [101,4091],
                        [102,247],
                        [103,85552],
                        [104,184674],
                        [105,72603],
                        [106,498],
                        [107,3253],
                        [108,1270],
                        [109,720],
                        [110,986],
                        [111,1376],
                        [112,890],
                        [113,745],
                        [114,221],
                        [115,609],
                        [116,633],
                        [117,629],
                        [118,212],
                        [119,1403],
                        [120,2005],
                        [121,1116],
                        [122,1452],
                        [123,1867],
                        [124,979],
                        [125,594],
                        [126,1195],
                        [127,658],
                        [128,317],
                        [129,430],
                        [130,445],
                        [131,264],
                        [132,493],
                        [133,161],
                        [134,486],
                        [135,378],
                        [136,378],
                        [137,409],
                        [138,2002],
                        [139,2692],
                        [140,963],
                        [141,331],
                        [142,684],
                        [143,803],
                        [144,561],
                        [145,508],
                        [146,432],
                        [147,160],
                        [148,301],
                        [149,294],
                        [150,149],
                        [151,229],
                        [152,176],
                        [153,437],
                        [154,1530],
                        [155,1032],
                        [156,710],
                        [157,1655],
                        [158,2260],
                        [159,1263],
                        [160,958],
                        [161,536],
                        [162,612],
                        [163,520],
                        [164,205],
                        [165,482],
                        [166,244],
                        [167,270],
                        [168,294],
                        [169,191],
                        [170,296],
                        [171,207],
                        [172,955],
                        [173,3985],
                        [174,2770],
                        [175,122],
                        [176,524],
                        [177,613],
                        [178,547],
                        [179,654],
                        [180,638],
                        [181,625],
                        [182,156],
                        [183,194],
                        [184,347],
                        [185,871],
                        [186,1162],
                        [187,677],
                        [188,550],
                        [189,1422],
                        [190,1790],
                        [191,961],
                        [192,883],
                        [193,1077],
                        [194,944],
                        [195,954],
                        [196,866],
                        [197,728],
                        [198,441],
                        [199,516],
                        [200,607],
                        [201,573],
                        [202,707],
                        [203,491],
                        [204,1041],
                        [205,2346],
                        [206,348],
                        [207,23435],
                        [208,45902],
                        [209,16783],
                        [210,252],
                        [211,1502],
                        [212,664],
                        [213,400],
                        [214,798],
                        [215,981],
                        [216,391],
                        [217,739],
                        [218,246],
                        [219,435],
                        [220,673],
                        [221,633],
                        [222,269],
                        [223,393],
                        [224,216],
                        [225,298],
                        [226,766],
                        [227,1896],
                        [228,860],
                        [229,296],
                        [230,719],
                        [231,169],
                        [232,140],
                        [233,359],
                        [234,609],
                        [235,483],
                        [236,410],
                        [237,155],
                        [238,376],
                        [239,243],
                        [240,251],
                        [241,838],
                        [242,3880],
                        [243,4322],
                        [244,991],
                        [245,465],
                        [246,524],
                        [247,453],
                        [248,705],
                        [249,646],
                        [250,589],
                        [251,214],
                        [252,322],
                        [253,257],
                        [254,288],
                        [255,107],
                        [256,453],
                        [257,501],
                        [258,1386],
                        [259,919],
                        [260,653],
                        [261,2761],
                        [262,3433],
                        [263,699],
                        [264,612],
                        [265,635],
                        [266,727],
                        [267,690],
                        [268,723],
                        [269,815],
                        [270,628],
                        [271,182],
                        [272,556],
                        [273,757],
                        [274,576],
                        [275,464],
                        [276,233],
                        [277,1414],
                        [278,897],
                        [279,70],
                        [280,671],
                        [281,904],
                        [282,759],
                        [283,121],
                        [284,177],
                        [285,243],
                        [286,260],
                        [287,273],
                        [288,388],
                        [289,404],
                        [290,192],
                        [291,437],
                        [292,388],
                        [293,1474],
                        [294,511],
                        [295,1846],
                        [296,6566],
                        [297,4779],
                        [298,947],
                        [299,251],
                        [300,99],
                        [301,247],
                        [302,180],
                        [303,654],
                        [304,462],
                        [305,194],
                        [306,44],
                        [307,263],
                        [308,293],
                        [309,961],
                        [310,195],
                        [311,10237],
                        [312,19208],
                        [313,6398],
                        [314,443],
                        [315,1229],
                        [316,420],
                        [317,841],
                        [318,963],
                        [319,598],
                        [320,565],
                        [321,249],
                        [322,332],
                        [323,250],
                        [324,547],
                        [325,577],
                        [326,205],
                        [327,563],
                        [328,656],
                        [329,307],
                        [330,1138],
                        [331,1948],
                        [332,554],
                        [333,497],
                        [334,167],
                        [335,456],
                        [336,383],
                        [337,228],
                        [338,115],
                        [339,266],
                        [340,208],
                        [341,214],
                        [342,391],
                        [343,171],
                        [344,236],
                        [345,1249],
                        [346,7777],
                        [347,7972],
                        [348,1068],
                        [349,1246],
                        [350,1525],
                        [351,1159],
                        [352,131],
                        [353,393],
                        [354,359],
                        [355,56],
                        [356,298],
                        [357,329],
                        [358,355],
                        [359,258],
                        [360,313],
                        [361,303],
                        [362,432],
                        [363,503],
                        [364,346],
                        [365,1320],
                        [366,1144],
                        [367,317],
                        [368,720],
                        [369,478],
                        [370,438],
                        [371,440],
                        [372,378],
                        [373,111],
                        [374,240],
                        [375,208],
                        [376,386],
                        [377,345],
                        [378,22],
                        [379,308],
                        [380,1668],
                        [381,4222],
                        [382,2666],
                        [383,315],
                        [384,934],
                        [385,676],
                        [386,379],
                        [387,693],
                        [388,977],
                        [389,583],
                        [390,232],
                        [391,256],
                        [392,359],
                        [393,555],
                        [394,308],
                        [395,349],
                        [396,522],
                        [397,1031],
                        [398,360],
                        [399,1438],
                        [400,4427],
                        [401,2833],
                        [402,212],
                        [403,321],
                        [404,175],
                        [405,421],
                        [406,348],
                        [407,547],
                        [408,310],
                        [409,135],
                        [410,376],
                        [411,449],
                        [412,308],
                        [413,884],
                        [414,83],
                        [415,4374],
                        [416,7551],
                        [417,2157],
                        [418,456],
                        [419,972],
                        [420,714],
                        [421,728],
                        [422,314],
                        [423,261],
                        [424,164],
                        [425,345],
                        [426,485],
                        [427,250],
                        [428,197],
                        [429,363],
                        [430,84],
                        [431,1079],
                        [432,1465],
                        [433,465],
                        [434,2962],
                        [435,4900],
                        [436,1491],
                        [437,341],
                        [438,625],
                        [439,530],
                        [440,301],
                        [441,192],
                        [442,349],
                        [443,459],
                        [444,291],
                        [445,25],
                        [446,422],
                        [447,254],
                        [448,231],
                        [449,994],
                        [450,5840],
                        [451,5814],
                        [452,861],
                        [453,1294],
                        [454,1554],
                        [455,1330],
                        [456,632],
                        [457,274],
                        [458,306],
                        [459,86],
                        [460,84],
                        [461,105],
                        [462,215],
                        [463,375],
                        [464,568],
                        [465,497],
                        [466,487],
                        [467,739],
                        [468,34],
                        [469,928],
                        [470,783],
                        [471,45],
                        [472,257],
                        [473,213],
                        [474,307],
                        [475,314],
                        [476,589],
                        [477,285],
                        [478,189],
                        [479,259],
                        [480,236],
                        [481,325],
                        [482,702],
                        [483,402],
                        [484,2574],
                        [485,7543],
                        [486,4487],
                        [487,586],
                        [488,1399],
                        [489,779],
                        [490,127],
                        [491,471],
                        [492,553],
                        [493,327],
                        [494,287],
                        [495,640],
                        [496,154],
                        [497,480],
                        [498,606],
                        [499,395],
                        [500,783],
                        [501,656],
                        [502,635],
                        [503,1348],
                        [504,3987],
                        [505,2809],
                        [506,215],
                        [507,323],
                        [508,452],
                        [509,160],
                        [510,220],
                        [511,367],
                        [512,202]
                    ];
                    this.isMounted = true;
                    return;
                }

 
                const axiosHeaders = {
                    headers: {
                        token: $nuxt.$store.state.auth.token,
                    },
                    params: { dId: this.config.selectedDevice.dId, variable: this.config.variable, chartTimeAgo: this.config.chartTimeAgo }
                }

                this.$axios.get("/get-small-charts-data", axiosHeaders)
                    .then(res => {
                        
                        this.chartOptions.series[0].data = [];
                        const data = res.data.data;
                        console.log(res.data)

                        data.forEach(element => {
                            var aux = []

                            aux.push(element.time + (new Date().getTimezoneOffset() * 60 * 1000 * -1));
                            aux.push(element.value);

                            this.chartOptions.series[0].data.push(aux);
                        });

                        this.isMounted = true;


                        return;

                    })
                    .catch(e => {

                        console.log(e)
                        return;

                    });

            },

            getIconColorClass() {

                if (this.config.class == "success") {
                    return "text-success";
                }
                if (this.config.class == "primary") {
                    return "text-primary";
                }
                if (this.config.class == "warning") {
                    return "text-warning";
                }
                if (this.config.class == "danger") {
                    return "text-danger";
                }
            },

            procesReceivedData(data) {

                try {
                    this.time = Date.now();
                    this.value = data.value;

                    setTimeout(() => {
                        if(data.save==1){
                            this.getChartData();
                        }  
                    }, 1000);
                } catch (error) {
                    console.log(error);
                }

               
            },

            getNow() {
                this.nowTime = Date.now();
                setTimeout(() => {
                    this.getNow();
                }, 1000);
            },

            getTimeAgo(seconds) {

                if (seconds < 0) {
                    seconds = 0;
                }

                if (seconds < 59) {
                    return seconds.toFixed() + " secs";
                }

                if (seconds > 59 && seconds <= 3600) {
                    seconds = seconds / 60;
                    return seconds.toFixed() + " min";
                }

                if (seconds > 3600 && seconds <= 86400) {
                    seconds = seconds / 3600;
                    return seconds.toFixed() + " hour";
                }

                if (seconds > 86400) {
                    seconds = seconds / 86400;
                    return seconds.toFixed() + " day";
                }


            },
        }
    };
</script>
<style></style>