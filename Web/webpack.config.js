var webpack = require('webpack')

module.exports = {
    entry: "./entry.ts",
    context: __dirname + "",
    output: {
        path: __dirname + "./../Resource",
        filename: "script.js"
    },
    devtool: 'inline-source-map',
    resolve: {
        extensions: ['.webpack.js', '.web.js', '.ts', '.js']
    },
    module: {
        loaders: [
            {
                exclude: /(node_modules)/,
                test: /\.ts$/,
                loader: 'ts-loader'
            }
        ]
    },
    plugins: [
        new webpack.ContextReplacementPlugin(
            /angular(\\|\/)core(\\|\/)(esm(\\|\/)src|src)(\\|\/)linker/,
            __dirname + "",
            {}
        )
    ]
};