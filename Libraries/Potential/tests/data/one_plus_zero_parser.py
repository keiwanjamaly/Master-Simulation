import json

if __name__ == "__main__":
    data = json.load(
        open('sc_i_on_1_10_100_n_800_xmax_10_lambda_1e6_tir_60_rg_flow.json', 'r'))

    # select first element where N = 3
    data = data[0]

    initial_condition = data[0]
    finial_condition = data[-1]

    print("hello world")
