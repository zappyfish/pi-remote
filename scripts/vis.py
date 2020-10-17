import matplotlib.pyplot as plt


def load_file(fname):
    with open(fname, 'r') as f:
        data = [ln for ln in f.readlines()]
    x = [0]
    if int(data[0][0]) == 1:
        y = [0]
    else:
        y = [1]

    for d in data:
        splt = d.split(',')
        next_y = int(splt[0])
        d_x = float(splt[1])

        last_x = x[len(x) - 1]
        x.append(last_x + 1)
        y.append(next_y)
        x.append(last_x + 1 + d_x)
        y.append(next_y)

    return x, y


def get_up_to(max_x, x, y):
    sub_x = []
    sub_y = []
    for i in range(len(x)):
        if x[i] > max_x:
            break
        sub_x.append(x[i])
        sub_y.append(y[i])

    return sub_x, sub_y


def plot_button(button, max_x=800e5):
    x, y = load_file(button + ".txt")
    # sub_x, sub_y = get_up_to(max_x, x, y)
    sub_x = x[93:105]
    sub_y = y[93:105]
    plt.plot(sub_x, sub_y)


max_x = 8e5

plot_button("on", max_x)
# plot_button("off", max_x)

plt.show()