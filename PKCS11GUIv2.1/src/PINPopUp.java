import javax.swing.*;

class PINPopUp {
    private JPanel panel1;
    private JLabel IncorrectPin;


    void buildPinPopUp() {
        JFrame frame2 = new JFrame("Incorrect Pin");
        frame2.setContentPane(new PINPopUp().panel1);
        frame2.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        frame2.pack();
        frame2.setLocationRelativeTo(null);
        frame2.setVisible(true);
    }

}
