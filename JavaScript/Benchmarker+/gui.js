
const SAMPLE_SIZE_CONTROL = document.getElementById('sample-size');
const SAMPLE_TYPE_CONTROL = document.getElementById('sample-type');
const GRAPH = document.getElementById('graph');

const ALGORITHM_CONTROL = document.getElementById('algorithm');
const RESULTS_TABLE = document.getElementById('results-table');


// Helpers
function format_time(time) {
    return time.toFixed(3) + 'ms';
}

// HTML Thingy's
function addDropdownOptions() {
    const average_option = document.createElement("option");
    average_option.textContent = "Promedio";

    for (const sample_size of samples_size) {
        let option = document.createElement('option');
        option.textContent = sample_size.toString();
        SAMPLE_SIZE_CONTROL.appendChild(option);
    }
    SAMPLE_SIZE_CONTROL.appendChild(average_option);

    for (const sample_type of sample_generators_name) {
        let option = document.createElement('option');
        option.textContent = sample_type.toString();
        SAMPLE_TYPE_CONTROL.appendChild(option);
    }
    SAMPLE_TYPE_CONTROL.appendChild(average_option.cloneNode(true));

    for (const algorithm of sorting_algorithms_name) {
        let option = document.createElement('option');
        option.textContent = algorithm;
        ALGORITHM_CONTROL.appendChild(option);
    }
}

function createGraphBars() {
    function createBar(algorithm) {
        const bar = document.createElement('div');
        bar.classList.add('graph-bar');

        const time_label = document.createElement('span');
        time_label.classList.add('label');
        time_label.innerText = '--.---ms';

        const bar_itself = document.createElement('div');
        bar_itself.classList.add('bar');
        //bar.style.height = height;

        const algorithm_label = document.createElement('span');
        algorithm_label.classList.add('label');
        algorithm_label.innerText = algorithm;

        bar.appendChild(time_label);
        bar.appendChild(bar_itself);
        bar.appendChild(algorithm_label);

        return bar;
    }

    for (const algorithm of sorting_algorithms_name) {
        GRAPH.appendChild(createBar(algorithm));
    }
}

function updateGraphValues() {
    const sample_type_index = SAMPLE_TYPE_CONTROL.selectedIndex;
    const sample_size_index = SAMPLE_SIZE_CONTROL.selectedIndex;

    let max = results[0][sample_type_index][sample_size_index];
    for (const result of results) {
        if (result[sample_type_index][sample_size_index] > max) {
            max = result[sample_type_index][sample_size_index];
        }
    }

    let i = 0;
    for (const bar of GRAPH.children) {
        const time_taken = results[i][sample_type_index][sample_size_index];

        const time_label = bar.children[0];
        time_label.innerText = format_time(time_taken);

        const bar_itself = bar.children[1];
        const percentage = time_taken / max * 100;
        bar_itself.style.height = percentage.toString() + '%';

        i++;
    }
}

function createResultsTable() {
    const header_row = document.createElement('tr');
    header_row.appendChild(document.createElement('th'));
    for (let i = 0; i <= samples_size.length; i++) {
        const header = document.createElement('th');
        header.innerText = i < samples_size.length ? samples_size[i].toString() : "Promedio";

        header_row.appendChild(header);
    }
    RESULTS_TABLE.appendChild(header_row);

    for (let i = 0; i <= sample_generators_name.length; i++) {
        const row = document.createElement('tr');

        const header = document.createElement('th');
        header.innerText = i < sample_generators_name.length ? sample_generators_name[i] : "Promedio";
        row.appendChild(header);

        for (let j = 0; j <= samples_size.length; j++) {
            const data = document.createElement('td');
            data.innerText = "--.---ms";

            row.appendChild(data);
        }

        RESULTS_TABLE.appendChild(row);
    }
}

function updateResultsTable() {
    const results_index = ALGORITHM_CONTROL.selectedIndex;
    const rs = results[results_index];

    for (let i = 1; i <= sample_generators.length + 1; i++) {
        for (let j = 1; j <= samples_size.length + 1; j++) {
            RESULTS_TABLE.children[i].children[j].innerText = format_time(rs[i - 1][j - 1]);
        }
    }
}

function updateRankings() {
    const RANKINGS = document.getElementById('rankings');
    RANKINGS.innerHTML = '';

    const sample_type_index = SAMPLE_TYPE_CONTROL.selectedIndex;
    const sample_size_index = SAMPLE_SIZE_CONTROL.selectedIndex;
    const rankings = Array.from(results);
    for (let i = 0; i < rankings.length; i++) {
        rankings[i].push(sorting_algorithms_name[i]);
    }

    rankings.sort((a, b) => a[sample_type_index][sample_size_index] - b[sample_type_index][sample_size_index]);
    for (const ranking of rankings) {
        const el = document.createElement('li');
        el.innerText = ranking.pop() + ": " + format_time(ranking[sample_type_index][sample_size_index]);

        RANKINGS.appendChild(el);
    }
}

function updateStuff() {
    updateGraphValues()
    updateRankings();
}

SAMPLE_SIZE_CONTROL.addEventListener('change', updateStuff);
SAMPLE_TYPE_CONTROL.addEventListener('change', updateStuff);

ALGORITHM_CONTROL.addEventListener('change', updateResultsTable);

window.onload = () => {
    runBenchmarks();

    addDropdownOptions();

    createGraphBars();
    updateStuff();

    createResultsTable();
    updateResultsTable();
}

