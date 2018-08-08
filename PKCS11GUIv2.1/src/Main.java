import javax.swing.*;


class Main {
    public static void main(String[] args) {
        JFrame frame = new JFrame("90Meter Java Interface");
        frame.setContentPane(new CardReaderGUI().CRGUI);
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        frame.pack();
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);

    }

}