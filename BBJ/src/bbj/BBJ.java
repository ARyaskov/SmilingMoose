/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj;

import bbj.graphicsobjects.*;

import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.*;

import javax.swing.border.*;
import java.awt.*;
import java.util.ArrayList;
import java.awt.event.*;
import java.io.File;
import javax.swing.*;
import javax.swing.JDialog;
import javax.swing.UIManager;
import javax.swing.filechooser.FileNameExtensionFilter;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerException;
import org.xml.sax.SAXException;
import javax.swing.undo.UndoableEditSupport;
import javax.swing.undo.*;
import javax.swing.event.*;

/**
 * JDK >= 1.4!
 *
 * @author Lemon
 */
public final class BBJ {

    /*
     * Поля класса для сохранения в файл.
     */
    private boolean m_hasFile;
    /**
     * Флаг наличия привязанного файла.
     */
    private String m_filename;
    /**
     * Имя файла, в который ведется сохранение.
     */
    public boolean m_hasModifications;
    /**
     * Флаг появления изменений с момента последнего сохранения.
     */
    public static Font menuFont;
    public static Font messageFont;
    public static Font messageTitleFont;
    public static Font borderTitleFont;
    public static Font tabTitleFont;
    public static Font commonArial;
    public static Font messageNameFont;
    public static Object qltAntialiasing = RenderingHints.VALUE_ANTIALIAS_OFF;
    public static Object qltTextAntialiasing1 = RenderingHints.VALUE_TEXT_ANTIALIAS_DEFAULT;
    public static Object qltTextAntialiasing2 = null;
    public static Object qltTextAntialiasing3 = null;
    public static Object qltTextAntialiasing4 = null;
    public static Object qltAlphaInterpolation = RenderingHints.VALUE_ALPHA_INTERPOLATION_SPEED;
    public static Object qltInterpolation = RenderingHints.VALUE_INTERPOLATION_NEAREST_NEIGHBOR;
    public static Object qltRender1 = RenderingHints.VALUE_RENDER_DEFAULT;
    public static Object qltRender2 = RenderingHints.VALUE_DITHER_DISABLE;
    public static Object qltRender3 = RenderingHints.VALUE_COLOR_RENDER_SPEED;
    public static Object qltRender4 = RenderingHints.VALUE_STROKE_PURE;
    public static Color m_background_color = new Color(255, 255, 255);
    
    public static double zoom; // пришлось дублировать тут
    public Font inputFont;
    public JMenu menuFile;
    public JMenu menuMisc;
    public JMenuItem createItem;
    public JMenuItem openItem;
    public JMenuItem saveItem;
    public JMenuItem saveAsItem;
    public JMenuItem importItem;
    public JMenu exportItem;
    public JToolBar toolBar;
    public JMenuItem inPictItem;
    public JMenuItem inXMIItem;
    public JMenuItem exitItem;
    public JFrame mainFrame;
    public JMenuBar menuBar;
    public static int windowHeight;
    public static int windowWidth;
    private ArrayList<String> itemsMessages;
    private ArrayList<String> itemsEntities;
    public UISelector m_messageSelector;
    public UISelector m_entitySelector;
    public JDialog prefsWindow;
    protected Scene canvas;
    private JPanel m_canvasUI;
    public static BBJ app;
    private UndoManager m_undoManager;
    private UndoableEditSupport m_undoSupport;
    public JButton m_undoButton;
    public JButton m_redoButton;
    public JButton delete_button;
    public JButton zoomin_button;
    public JButton zoomout_button;

    public Scene getScene() {
        return canvas;
    }

    public JPanel getCanvasUI() {
        return m_canvasUI;
    }

    public BBJ() {
        setupFonts();
        fillGUIContent();
        setupUndoRedo();
        bindListeners();
        m_hasFile = false;
        m_hasModifications = false;

    }

    public UndoManager getUndoManager() {
        return m_undoManager;
    }

    public UndoableEditSupport getUndoSupport() {
        return m_undoSupport;
    }

    public void setupUndoRedo() {


        m_undoManager = new UndoManager();
        m_undoSupport = new UndoableEditSupport();


        UndoableEditListener listener = new UndoableEditListener() {

            public void undoableEditHappened(UndoableEditEvent e) {
                m_undoManager.addEdit(e.getEdit());
            }
        };

        m_undoSupport.addUndoableEditListener(listener);

        /*
         * Action undoAction = new UndoAction(m_undoManager); Action redoAction
         * = new RedoAction(m_undoManager); // Assign the actions to keys
         * ((JComponent)mainFrame.getContentPane()).registerKeyboardAction(
         * undoAction, KeyStroke.getKeyStroke(KeyEvent.VK_Z,
         * InputEvent.CTRL_MASK), JComponent.WHEN_IN_FOCUSED_WINDOW);
         * ((JComponent)mainFrame.getContentPane()).registerKeyboardAction(redoAction,
         * KeyStroke.getKeyStroke(KeyEvent.VK_Y, InputEvent.CTRL_MASK),
         * JComponent.WHEN_IN_FOCUSED_WINDOW);
         */
    }

    public void repaintSelectors() {
        if (m_messageSelector != null && m_entitySelector != null) {
            m_messageSelector.repaint();
            m_entitySelector.repaint();
        }
    }

    public void fillGUIContent() {
        mainFrame = new JFrame();
        menuBar = new JMenuBar();
        toolBar = new JToolBar(JToolBar.HORIZONTAL);
        itemsMessages = new ArrayList<String>();
        itemsEntities = new ArrayList<String>();

        setupMenus(menuBar);
        mainFrame.setJMenuBar(menuBar);

        toolBar.setFloatable(false);
        toolBar.setBorder(new BevelBorder(BevelBorder.RAISED));
        fillToolBar();

        mainFrame.add(toolBar, "North");


        itemsMessages.add("Reply");
        itemsMessages.add("Create");
        itemsMessages.add("Message");
        itemsMessages.add("Delete");
        itemsMessages.add("Sync");
        itemsMessages.add("Async");



        itemsEntities.add("Actor");
        itemsEntities.add("Comment");
        itemsEntities.add("LifeLine");

        m_messageSelector = new UISelector(
                itemsMessages,
                2,
                "images/48/",
                "images/24/",
                "images/16/",
                "message");
        m_entitySelector = new UISelector(
                itemsEntities,
                2,
                "images/48/",
                "images/24/",
                "images/16/",
                "entity");

        canvas = new Scene(this);
        canvas.setSize(mainFrame.getWidth()+100, mainFrame.getHeight() - toolBar.getHeight()
                - menuBar.getHeight()+100);

        mainFrame.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
        ArrayList<Image> listOfIcons = new ArrayList();
        listOfIcons.add(new ImageIcon(BBJ.class.getResource("images/moose16.png")).getImage());
        listOfIcons.add(new ImageIcon(BBJ.class.getResource("images/moose24.png")).getImage());
        listOfIcons.add(new ImageIcon(BBJ.class.getResource("images/moose48.png")).getImage());
        listOfIcons.add(new ImageIcon(BBJ.class.getResource("images/moose64.png")).getImage());
        listOfIcons.add(new ImageIcon(BBJ.class.getResource("images/moose128.png")).getImage());
        mainFrame.setIconImages(listOfIcons);


        mainFrame.setTitle("Smiling Moose");
        mainFrame.setSize(800, 600);
        mainFrame.setLocationRelativeTo(null);
        mainFrame.setMinimumSize(new Dimension(400, 400));
        mainFrame.setMaximumSize(new Dimension(2560, 1600));


        mainFrame.add(m_messageSelector);
        mainFrame.add(m_entitySelector);

        m_messageSelector.setLocation(5, 55);
        m_entitySelector.setLocation(5, m_messageSelector.getY() + m_messageSelector.getHeight() + 10);

        mainFrame.add(canvas);

        mainFrame.addWindowListener(new mainFrameWindowListener());

       // JScrollPane scroll = new JScrollPane(canvas);
      //  scroll.setViewportView(canvas);
        mainFrame.setVisible(true);


    }

    class mainFrameWindowListener implements ComponentListener, WindowListener {

        public void windowActivated(WindowEvent event) {
        }

        public void windowClosed(WindowEvent event) {
        }

        public void windowClosing(WindowEvent event) {
            Object[] options = {"Да", "Нет!"};
            int n = JOptionPane.showOptionDialog(event.getWindow(), "Закрыть Smiling Moose?",
                    "Подтверждение", JOptionPane.YES_NO_OPTION,
                    JOptionPane.QUESTION_MESSAGE, null, options,
                    options[0]);
            if (n == 0) {
                if (m_hasModifications) {
                    try {
                        saveDialog();
                    } catch (ParserConfigurationException ex) {
                        Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (SAXException ex) {
                        Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (IOException ex) {
                        Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (TransformerConfigurationException ex) {
                        Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (TransformerException ex) {
                        Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                    }
                }
                event.getWindow().setVisible(false);
                System.exit(0);
            }
        }

        public void windowDeactivated(WindowEvent event) {
        }

        public void windowDeiconified(WindowEvent event) {
        }

        public void windowIconified(WindowEvent event) {
            canvas.repaint();
        }

        public void windowOpened(WindowEvent event) {
            canvas.repaint();
        }

        public void componentHidden(ComponentEvent e) {
        }

        public void componentMoved(ComponentEvent e) {
        }

        public void componentResized(ComponentEvent e) {
            windowHeight = e.getComponent().getHeight();
            windowWidth = e.getComponent().getWidth();
            //Убрать когда скролл сделаем
            BBJ.app.getScene().setSize(windowWidth, windowHeight);
            BBJ.app.getScene().repaint();
        }

        public void componentShown(ComponentEvent e) {
        }
    }

    public void setupMenus(JMenuBar menuBar) {

        menuFile = new JMenu("Файл");
        menuFile.setFont(menuFont);

        menuBar.add(menuFile);

        menuMisc = new JMenu("Прочее");
        menuMisc.setFont(menuFont);

        menuBar.add(menuMisc);

        createItem = new JMenuItem("Создать");
        menuFile.add(createItem);
        createItem.setFont(menuFont);
        createItem.setAccelerator(KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_N,
                java.awt.Event.CTRL_MASK));
        createItem.addActionListener(new ActionListener() {

            /**
             * Метод создания новой диаграммы.
             */
            @Override
            public void actionPerformed(ActionEvent e) {
                if (m_hasModifications) {
                    try {
                        saveDialog();
                    } catch (ParserConfigurationException ex) {
                        Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (SAXException ex) {
                        Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (IOException ex) {
                        Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (TransformerConfigurationException ex) {
                        Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (TransformerException ex) {
                        Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                    }
                }
                canvas.clear();
                m_hasFile = false;
                m_filename = "";
            }
        });

        openItem = new JMenuItem("Открыть...");
        menuFile.add(openItem);
        openItem.setFont(menuFont);
        openItem.setAccelerator(KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_O,
                java.awt.Event.CTRL_MASK));
        openItem.addActionListener(new ActionListener() {

            /**
             * Метод открытия файла с диаграммой.
             */
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser chooser = new JFileChooser();
                FileNameExtensionFilter filter = new FileNameExtensionFilter(
                        "Smilling Moose Projects files (*.suef,*.suefd)", "suef", "suefd");
                chooser.setFileFilter(filter);
                int returnVal = chooser.showOpenDialog(mainFrame);
                if (returnVal == JFileChooser.APPROVE_OPTION) {
                    File file = chooser.getSelectedFile();
                    m_hasFile = true;
                    m_filename = file.getPath();
                    if (m_hasModifications) {
                        try {
                            saveDialog();
                        } catch (ParserConfigurationException ex) {
                            Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                        } catch (SAXException ex) {
                            Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                        } catch (IOException ex) {
                            Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                        } catch (TransformerConfigurationException ex) {
                            Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                        } catch (TransformerException ex) {
                            Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                        }
                    }
                    try {
                        canvas.clear();
                        canvas.load(m_filename);
                    } catch (ParserConfigurationException ex) {
                        Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (SAXException ex) {
                        Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (IOException ex) {
                        Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                    }
                }
            }
        });

        saveItem = new JMenuItem("Сохранить");
        menuFile.add(saveItem);
        saveItem.setFont(menuFont);
        saveItem.setAccelerator(KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_S,
                java.awt.Event.CTRL_MASK));
        saveItem.addActionListener(new ActionListener() {

            /**
             * Метод сохранения диаграммы по пункту меню "Сохранить".
             */
            @Override
            public void actionPerformed(ActionEvent e) {
                if (!m_hasFile) {
                    saveFileUs();
                } else {
                    try {
                        canvas.save(m_filename);
                    } catch (ParserConfigurationException ex) {
                        Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (SAXException ex) {
                        Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (IOException ex) {
                        Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (TransformerConfigurationException ex) {
                        Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (TransformerException ex) {
                        Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                    }
                }
            }
        });

        saveAsItem = new JMenuItem("Сохранить как...");
        menuFile.add(saveAsItem);
        saveAsItem.setFont(menuFont);
        saveAsItem.setAccelerator(KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_S,
                java.awt.Event.CTRL_MASK + java.awt.Event.SHIFT_MASK));
        saveAsItem.addActionListener(new ActionListener() {

            /**
             * Метод сохранения диаграммы в указанный файл.
             */
            @Override
            public void actionPerformed(ActionEvent e) {
                saveFileUs();
            }
        });

        menuFile.addSeparator();

        importItem = new JMenuItem("Импорт из XML...");
        menuFile.add(importItem);
        importItem.setFont(menuFont);
        importItem.addActionListener(new ActionListener() {

            /**
             * Метод открытия файла с диаграммой. Метод импорта диаграммы из xml
             * файла.
             */
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser chooser = new JFileChooser();
                FileNameExtensionFilter filter = new FileNameExtensionFilter(
                        "XML files (*.xml)", "xml");
                chooser.setFileFilter(filter);
                int returnVal = chooser.showOpenDialog(mainFrame);
                if (returnVal == JFileChooser.APPROVE_OPTION) {
                    File file = chooser.getSelectedFile();
                    if (m_hasModifications) {
                        try {
                            saveDialog();
                        } catch (ParserConfigurationException ex) {
                            Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                        } catch (SAXException ex) {
                            Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                        } catch (IOException ex) {
                            Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                        } catch (TransformerConfigurationException ex) {
                            Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                        } catch (TransformerException ex) {
                            Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                        }
                    }
                    try {
                        canvas.load(file.getPath());
                    } catch (ParserConfigurationException ex) {
                        Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (SAXException ex) {
                        Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (IOException ex) {
                        Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                    }
                }
            }
        });

        exportItem = new JMenu("Экспорт");
        menuFile.add(exportItem);
        exportItem.setFont(menuFont);

        inPictItem = new JMenuItem("в картинку...");
        exportItem.add(inPictItem);
        inPictItem.setFont(menuFont);
        inPictItem.addActionListener(new ActionListener() {

            /**
             * Метод сохранения диаграммы в указанный графический файл.
             * Диаграмма будет сохранена в виде изображения.
             */
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser chooser = new JFileChooser();
                FileNameExtensionFilter filter = new FileNameExtensionFilter(
                        "Draw images (*.png)", "png");
                chooser.setFileFilter(filter);
                int returnVal = chooser.showSaveDialog(mainFrame);
                if (returnVal == JFileChooser.APPROVE_OPTION) {
                    File file = chooser.getSelectedFile();
                }
            }
        });

        inXMIItem = new JMenuItem("в XML файл...");
        exportItem.add(inXMIItem);
        inXMIItem.setFont(menuFont);
        inXMIItem.addActionListener(new ActionListener() {

            /**
             * Метод сохранения диаграммы в указанный xml файл.
             */
            @Override
            public void actionPerformed(ActionEvent e) {
                JFileChooser chooser = new JFileChooser();
                FileNameExtensionFilter filter = new FileNameExtensionFilter(
                        "XML files (*.xml)", "xml");
                chooser.setFileFilter(filter);
                int returnVal = chooser.showSaveDialog(mainFrame);
                if (returnVal == JFileChooser.APPROVE_OPTION) {
                    File file = chooser.getSelectedFile();
                    String filePath = file.getPath();
                    if (!filePath.matches(".+\\..+")) {
                        String[] ps = ((FileNameExtensionFilter) chooser.getFileFilter()).getExtensions();
                        filePath += ("." + ps[0]);
                    }
                    try {
                        canvas.save(filePath);
                    } catch (ParserConfigurationException ex) {
                        Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (SAXException ex) {
                        Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (IOException ex) {
                        Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (TransformerConfigurationException ex) {
                        Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                    } catch (TransformerException ex) {
                        Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                    }
                }
            }
        });





        /*
         * == Misc Menu ==
         */
        JMenuItem prefersItem = new JMenuItem("Настройки");
        menuMisc.add(prefersItem);
        prefersItem.setFont(menuFont);
        prefersItem.addActionListener(new ActionListener() {

            public void actionPerformed(ActionEvent e) {
                prefsWindow = new PreferenceWindow(mainFrame, "Настройки", true);
                prefsWindow.setLocationRelativeTo(mainFrame.getContentPane());
                prefsWindow.setVisible(true);
            }
        });


        menuMisc.addSeparator();

        JMenuItem helpItem = new JMenuItem("Справка");
        menuMisc.add(helpItem);
        helpItem.setFont(menuFont);
        helpItem.setAccelerator(KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_F1, java.awt.Event.ALT_MASK));
        helpItem.addActionListener(new ActionListener() {

            /**
             * Метод вызова справки через браузер пользователя.
             */
            @Override
            public void actionPerformed(ActionEvent e) {
                String url = "help/index.html";
                String os = System.getProperty("os.name").toLowerCase();
                Runtime rt = Runtime.getRuntime();

                if (os.indexOf("win") >= 0) {
                    try {
                        rt.exec("rundll32 url.dll,FileProtocolHandler " + url);
                    } catch (IOException ex) {
                        Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                    }
                } else if (os.indexOf("mac") >= 0) {
                    try {
                        rt.exec("open " + url);
                    } catch (IOException ex) {
                        Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                    }
                } else if (os.indexOf("nix") >= 0 || os.indexOf("nux") >= 0) {
                    String[] browsers = {"epiphany", "firefox", "mozilla", "konqueror",
                        "netscape", "opera", "links", "lynx"};
                    StringBuffer cmd = new StringBuffer();
                    for (int i = 0; i < browsers.length; i++) {
                        cmd.append((i == 0 ? "" : " || ") + browsers[i] + " \"" + url + "\" ");
                    }
                    try {
                        rt.exec(new String[]{"sh", "-c", cmd.toString()});
                    } catch (IOException ex) {
                        Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                    }
                }
            }
        });



    }

    public void setupFonts() {
        int dpi = Toolkit.getDefaultToolkit().getScreenResolution();
        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();



        commonArial = new Font("Arial",
                Font.PLAIN, 11);

        menuFont = new Font("Arial",
                Font.PLAIN, 11);
        messageFont = new Font("Arial",
                Font.PLAIN, 11);
        messageTitleFont = new Font("Arial",
                Font.PLAIN, 11);
        borderTitleFont = new Font("Georgia",
                Font.PLAIN, 13);
        tabTitleFont = new Font("Arial",
                Font.PLAIN, 12);
        messageNameFont = new Font("Georgia",
                Font.PLAIN, 14);
        UIManager.put("Label.font", BBJ.commonArial);


    }

    public void fillToolBar() {


        toolBar.add(new JToolBar.Separator(new Dimension(150, toolBar.getHeight())));

        JToggleButton select_button = new JToggleButton();
        select_button.setIcon(new ImageIcon(BBJ.class.getResource("images/32/cursor.png")));
        toolBar.add(select_button);

        toolBar.add(new JToolBar.Separator(new Dimension(5, toolBar.getHeight())));

        delete_button = new JButton();
        delete_button.setIcon(new ImageIcon(BBJ.class.getResource("images/32/bin.png")));
        toolBar.add(delete_button);
        delete_button.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                canvas.removeSelectedItems();
            }
        });

        toolBar.add(new JToolBar.Separator(new Dimension(60, toolBar.getHeight())));

        /*
         * JToggleButton message_button = new JToggleButton();
         * message_button.setIcon(new
         * ImageIcon(BBJ.class.getResource("images/message_arrow.png")));
         * toolBar.add(message_button);
         *
         * JToggleButton lifeline_button = new JToggleButton();
         * lifeline_button.setIcon(new
         * ImageIcon(BBJ.class.getResource("images/lifeline_arrow.png")));
         * toolBar.add(lifeline_button);
         *
         * JToggleButton freecomment_button = new JToggleButton();
         * freecomment_button.setIcon(new
         * ImageIcon(BBJ.class.getResource("images/comment.png")));
         * toolBar.add(freecomment_button);
         *
         * JToolBar.Separator sep2 = new JToolBar.Separator(new
         * Dimension(20,toolBar.getHeight())); toolBar.add(sep2);
         */
        m_undoButton = new JButton();
        m_undoButton.setIcon(new ImageIcon(BBJ.class.getResource("images/32/undo.png")));
        m_undoButton.setEnabled(false);
        //undo_button.setText("Undo");
        toolBar.add(m_undoButton);

        toolBar.add(new JToolBar.Separator(new Dimension(5, toolBar.getHeight())));

        m_redoButton = new JButton();
        m_redoButton.setIcon(new ImageIcon(BBJ.class.getResource("images/32/redo.png")));
        m_redoButton.setEnabled(false);
        toolBar.add(m_redoButton);

        toolBar.add(new JToolBar.Separator(new Dimension(60, toolBar.getHeight())));


        zoomin_button = new JButton();
        zoomin_button.setIcon(new ImageIcon(BBJ.class.getResource("images/32/zoom_in.png")));
        toolBar.add(zoomin_button);

        toolBar.add(new JToolBar.Separator(new Dimension(5, toolBar.getHeight())));

        zoomout_button = new JButton();
        zoomout_button.setIcon(new ImageIcon(BBJ.class.getResource("images/32/zoom_out.png")));
        toolBar.add(zoomout_button);
    }

    /**
     * Метод вызываемый при выборе меню "Сохранить как..."
     */
    private void saveFileUs() {

        JFileChooser chooser = new JFileChooser();
        FileNameExtensionFilter filter = new FileNameExtensionFilter(
                "Smiling Moose Projects files (*.suef)", "suef");
        chooser.setFileFilter(filter);
        chooser.addChoosableFileFilter(filter);
        chooser.addChoosableFileFilter(new FileNameExtensionFilter("Smiling Moose Draft Projects files (*.suefd)",
                "suefd"));
        int returnVal = chooser.showSaveDialog(mainFrame);
        if (returnVal == JFileChooser.APPROVE_OPTION) {
            File file = chooser.getSelectedFile();
            String filePath = file.getPath();
            m_hasFile = true;
            if (!filePath.matches(".+\\..+")) {
                String[] ps = ((FileNameExtensionFilter) chooser.getFileFilter()).getExtensions();
                filePath += ("." + ps[0]);
            }
            m_filename = filePath;
            try {
                try {
                    canvas.save(filePath);
                } catch (TransformerConfigurationException ex) {
                    Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                } catch (TransformerException ex) {
                    Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                }
            } catch (ParserConfigurationException ex) {
                Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
            } catch (SAXException ex) {
                Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
            } catch (IOException ex) {
                Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }

    public void bindListeners() {

        MouseAdapter undoButtonListener = new MouseAdapter() {

            public void mouseClicked(MouseEvent e) {
                if (e.getButton() == MouseEvent.BUTTON1 && m_undoButton.isEnabled()) {
                    getUndoManager().undo();
                    m_undoButton.setEnabled(getUndoManager().canUndo());
                    m_redoButton.setEnabled(getUndoManager().canRedo());
                }
            }

            public void mouseEntered(MouseEvent e) {
                m_undoButton.setToolTipText(getUndoManager().getUndoPresentationName());
            }
        };

        MouseAdapter redoButtonListener = new MouseAdapter() {

            public void mouseClicked(MouseEvent e) {
                if (e.getButton() == MouseEvent.BUTTON1 && m_redoButton.isEnabled()) {

                    getUndoManager().redo();
                    m_redoButton.setEnabled(getUndoManager().canRedo());
                    m_undoButton.setEnabled(getUndoManager().canUndo());


                }
            }

            public void mouseEntered(MouseEvent e) {
                m_redoButton.setToolTipText(getUndoManager().getRedoPresentationName());
            }
        };



        m_undoButton.addMouseListener(undoButtonListener);
        m_redoButton.addMouseListener(redoButtonListener);


        ActionListener undoKeyListener = new ActionListener() {

            public void actionPerformed(ActionEvent a) {
                getUndoManager().undo();
                m_undoButton.setEnabled(getUndoManager().canUndo());
                m_redoButton.setEnabled(getUndoManager().canRedo());
                m_undoButton.setToolTipText(getUndoManager().getUndoPresentationName());
            }
        };

        ActionListener redoKeyListener = new ActionListener() {

            public void actionPerformed(ActionEvent a) {
                getUndoManager().redo();
                m_redoButton.setEnabled(getUndoManager().canRedo());
                m_undoButton.setEnabled(getUndoManager().canUndo());
                m_redoButton.setToolTipText(getUndoManager().getRedoPresentationName());
            }
        };

        ActionListener zoomInKeyListener = new ActionListener() {

            public void actionPerformed(ActionEvent a) {
                canvas.setZoom(canvas.getZoom()+0.05);
                canvas.repaint();
            }
        };
        
        ActionListener zoomOutKeyListener = new ActionListener() {

            public void actionPerformed(ActionEvent a) {
                canvas.setZoom(canvas.getZoom()-0.05);
                canvas.repaint();
            }
        };
        

        zoomin_button.addActionListener(zoomInKeyListener);
        zoomout_button.addActionListener(zoomOutKeyListener);
        

        ((JComponent) m_undoButton).registerKeyboardAction(
                undoKeyListener,
                KeyStroke.getKeyStroke(KeyEvent.VK_Z, Toolkit.getDefaultToolkit().getMenuShortcutKeyMask()),
                JComponent.WHEN_IN_FOCUSED_WINDOW);

        ((JComponent) m_redoButton).registerKeyboardAction(
                redoKeyListener,
                KeyStroke.getKeyStroke(KeyEvent.VK_Y, Toolkit.getDefaultToolkit().getMenuShortcutKeyMask()),
                JComponent.WHEN_IN_FOCUSED_WINDOW);




        // Тут цепляем слушателей к кнопкам



    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        app = new BBJ();
    }

    /**
     * Диалог сохранения диаграммы при закрытии программы.
     */
    private void saveDialog() throws ParserConfigurationException, SAXException, IOException, TransformerConfigurationException, TransformerException {
        Object[] options = {"Да", "Нет!"};

        int answer = JOptionPane.showOptionDialog(this.mainFrame, "Сохранить изменения в проекте?",
                "Подтверждение", JOptionPane.YES_NO_OPTION,
                JOptionPane.QUESTION_MESSAGE, null, options,
                options[0]);
        if (answer == 0) {
            if (!m_hasFile) {
                saveFileUs();
            } else {
                canvas.getModel().save(m_filename);
            }
        }
    }
}
