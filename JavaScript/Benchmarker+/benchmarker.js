class Benchmarker {
    constructor(sample_sizes, sample_generators) {
        this.sample_sizes = sample_sizes;
        this.sample_generators = sample_generators;
    }

    runBenchmark(sorting_algorithm) {
        let results = this.#getTimes(sorting_algorithm);
        this.#addAverages(results);

        return results;
    }

    #getTimes(sorting_algorithm) {
        let results = new Array(sample_generators.length);
        for (let i = 0; i < sample_generators.length; i++) {
            results[i] = new Array(samples_size.length).fill(-1);
        }

        let i = 0;
        for (const generator of sample_generators) {
            let j = 0;
            for (const size of samples_size) {
                let sample = new Array(size);
                generator(sample);
                // if (size === 100) {
                //     console.log(generator.name);
                //     console.log(sample);
                // }

                const start = performance.now();
                sorting_algorithm(sample);
                const end = performance.now();

                results[i][j] = end - start;
                j++;
            }
            i++;
        }
        return results;
    }

    #addAverages(results) {
        const types = sample_generators.length;
        const sizes = samples_size.length;

        // Sample type averages
        for (const sample_type_results of results) {
            let type_average = 0;
            for (const size_result of sample_type_results) {
                type_average += Number(size_result);
            }

            sample_type_results.push(type_average / sizes);
        }

        // Size average + total average
        let size_averages = new Array(sizes+1).fill(0);
        for (const sample_type_results of results) {
            for (let i = 0; i <= sizes; i++) {
                size_averages[i] += sample_type_results[i] / types;
            }
        }

        results.push(size_averages);
    }
}