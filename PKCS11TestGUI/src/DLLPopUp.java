
import javax.swing.*;

class DLLPopUp {
    private JPanel OSPopUp;
    private JLabel IncorrectDLL;

    void buildPopUp() {
        JFrame frame1 = new JFrame("Incorrect DLL");
        frame1.setContentPane(new DLLPopUp().OSPopUp);
        frame1.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        frame1.pack();
        frame1.setLocationRelativeTo(null);
        frame1.setVisible(true);
    }
}
