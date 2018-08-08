import javax.swing.*;
import java.io.File;
import java.io.IOException;
import java.security.KeyStore;
import java.security.KeyStoreException;
import java.security.ProviderException;
import java.security.cert.X509Certificate;
import java.util.Enumeration;


class CardReaderGUI {
    public JPanel CRGUI;
    private CardReader cr = new CardReader();
    private DLLPopUp dllgui = new DLLPopUp();
    private PINPopUp p = new PINPopUp();
    private JPasswordField PINPasswordField;
    private JButton enterButton;
    private JLabel Browser;
    private JTextField BrowserText;
    private JButton browseButton;
    private JLabel Title;
    private JLabel Logo;
    private JTextPane CertView;

    /**
     * Implements the various actions performed on the UI
     */
    CardReaderGUI() {
        ImageIcon iconLogo = new ImageIcon(getClass().getResource("image/90meterlogo.png"));
        Logo.setIcon(iconLogo);

        browseButton.addActionListener(e -> {
            JFrame fframe = new JFrame();
            JFileChooser chooser = new JFileChooser("C:\\");
            int option = chooser.showOpenDialog(fframe);
            if (option == JFileChooser.APPROVE_OPTION) {
                File selectedFile = chooser.getSelectedFile();
                String path = selectedFile.getAbsolutePath();
                BrowserText.setText(path);
                path.replace("\\", "\\\\");
                cr.setLibrary(path);
                cr.makeConfig();
            }
        });

        enterButton.addActionListener(e -> {
            char[] PIN;
            if (BrowserText.getText().isEmpty()) {
                dllgui.buildPopUp();
            } else {
                cr.loadProvider();
                PIN = PINPasswordField.getPassword();
                cr.setPin(PIN);
                try {
                    cr.buildKeyStore();
                    KeyStore ks = cr.getKeyStore();
                    Enumeration<String> aliases = ks.aliases();
                    while (aliases.hasMoreElements()) {
                        String alias = aliases.nextElement();
                        CertView.setText(CertView.getText() + "Certificate for: \n" +
                                alias.replaceAll(",", ", ")
                                + " \n");
                        X509Certificate cert = (X509Certificate) ks.getCertificate(alias);
                        CertView.setText(CertView.getText() + "Serial Number: \n" +
                                cert.getSerialNumber().toString(16).toUpperCase()
                                + " \n\n");
                    }
                    PINPasswordField.setText("");
                } catch (ProviderException ex) {
                    if (ex.getCause() instanceof IOException) {
                        dllgui.buildPopUp();
                    } else
                        ex.printStackTrace();
                } catch (KeyStoreException ex) {
                    if (ex.getCause() instanceof IOException) {
                        PINPasswordField.setText("");
                        p.buildPinPopUp();
                    } else if (ex.getCause() instanceof KeyStoreException) {
                        cr.checkInserted();
                    } else
                        ex.printStackTrace();
                }
            }
            cr.cleanUp();
        });
    }
}
