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
import javax.swing.JDialog;
import javax.swing.UIManager;
import javax.swing.filechooser.FileNameExtensionFilter;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerException;
import org.xml.sax.SAXException;

/** JDK >= 1.4!
 *
 * @author Lemon
 */
public final class BBJ {
    
    /* Поля класса для сохранения в файл. */
    private boolean m_hasFile;  /** Флаг наличия привязанного файла. */
    private String  m_filename; /** Имя файла, в который ведется сохранение. */

    public static Font menuFont;
    public static Font messageFont;
    public static Font messageTitleFont;
    public static Font borderTitleFont;
    public static Font tabTitleFont;
    public static Font commonArial;
    public static Font messageNameFont;
    
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
    
    
    public static int windowHeight;
    public static int windowWidth;
    
    public JDialog prefsWindow;
    
    protected Scene canvas;
    public static BBJ app;
    
    public Scene getScene(){
        return canvas;
    }
    
    
    public BBJ(){
        setupFonts();
        fillGUIContent();
        bindListeners();
        
    }
    
    
 
     public void fillGUIContent(){
         mainFrame = new JFrame();
         mainFrame.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE );
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
         mainFrame.setMinimumSize(new Dimension(400,400));
         mainFrame.setMaximumSize(new Dimension(2560,1600));
         
         JMenuBar menuBar = new JMenuBar();
         setupMenus(menuBar);
         mainFrame.setJMenuBar(menuBar);
       
         
         toolBar = new JToolBar(JToolBar.HORIZONTAL);
         toolBar.setFloatable(false);
         toolBar.setBorder(new BevelBorder(BevelBorder.RAISED));
         fillToolBar();
         mainFrame.add(toolBar, "North");

         canvas = new Scene();
       
         canvas.setSize(mainFrame.getWidth()+100, mainFrame.getHeight() - toolBar.getHeight()
                 - menuBar.getHeight());
         
         
         /*JViewport viewport = new JViewport();
         viewport.setView(canvas);
         mainFrame.add(viewport);*/
          final JScrollPane scrollPane = new JScrollPane(canvas);
           mainFrame.add(scrollPane, BorderLayout.CENTER);
         
         mainFrame.add(canvas);
         
         mainFrame.addWindowListener(new mainFrameWindowListener());
         
         mainFrame.setVisible(true);
         
     }
     
      class mainFrameWindowListener implements ComponentListener, WindowListener {

			public void windowActivated(WindowEvent event) {}
			public void windowClosed(WindowEvent event) {}
                        public void windowClosing(WindowEvent event) {
				Object[] options = { "Да", "Нет!" };
				int n = JOptionPane
						.showOptionDialog(event.getWindow(), "Закрыть Smiling Moose?",
								"Подтверждение", JOptionPane.YES_NO_OPTION,
								JOptionPane.QUESTION_MESSAGE, null, options,
								options[0]);
				if (n == 0) {
					event.getWindow().setVisible(false);
					System.exit(0);
				}
			}
			public void windowDeactivated(WindowEvent event) {}
			public void windowDeiconified(WindowEvent event) {}
			public void windowIconified(WindowEvent event) {canvas.repaint();}
			public void windowOpened(WindowEvent event) {canvas.repaint();}
                        
                        public void componentHidden(ComponentEvent e){
                            
                        }  
                        public void componentMoved(ComponentEvent e){
                            
                        }  
                        public void componentResized(ComponentEvent e){
                           windowHeight = e.getComponent().getHeight();
                           windowWidth = e.getComponent().getWidth();
                           BBJ.app.getScene().updateUI();
                        }
                        public void componentShown(ComponentEvent e){
                            
                        }
         
                        
      }
     
     public void setupMenus(JMenuBar menuBar){
     
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
                }
            }
        });
         
         saveItem = new JMenuItem("Сохранить");
         menuFile.add(saveItem);
         saveItem.setFont(menuFont);
         saveItem.setAccelerator(KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_S,
                 java.awt.Event.CTRL_MASK));
         
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
                   saveFileUs ();
            }
        });
         
         menuFile.addSeparator();
         
         importItem = new JMenuItem("Импорт из XML...");
         menuFile.add(importItem);
         importItem.setFont(menuFont);
         importItem.addActionListener(new ActionListener() {

            /**
              * Метод открытия файла с диаграммой.
              * Метод импорта диаграммы из xml файла.
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
                        String[] ps = ((FileNameExtensionFilter)chooser.getFileFilter()).getExtensions(); 
                        filePath += ("." + ps[0]);
                     }
                    try {
                        canvas.getModel().save(filePath);
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
         
         
 
         
         
         /* == Misc Menu ==*/
         JMenuItem prefersItem = new JMenuItem("Настройки");
         menuMisc.add(prefersItem);
         prefersItem.setFont(menuFont);
         prefersItem.addActionListener(new ActionListener()
             {public void actionPerformed(ActionEvent e)
             {prefsWindow = new PreferenceWindow(mainFrame, "Настройки", true);
             prefsWindow.setLocationRelativeTo(mainFrame.getContentPane());
             prefsWindow.setVisible(true);} });
         
         
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
                String url = "index.html";
                String os = System.getProperty("os.name").toLowerCase();
                Runtime rt = Runtime.getRuntime();
                
                if (os.indexOf("win") >= 0) {
                    try {
                        rt.exec( "rundll32 url.dll,FileProtocolHandler " + url);
                    } catch (IOException ex) {
                        Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                    }
                } else if (os.indexOf( "mac" ) >= 0) {
                    try {
                        rt.exec( "open " + url);
                    } catch (IOException ex) {
                        Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                    }
                } else if (os.indexOf( "nix") >=0 || os.indexOf( "nux") >=0) {
                    String[] browsers = {"epiphany", "firefox", "mozilla", "konqueror",
	       			             "netscape","opera","links","lynx"};
                    StringBuffer cmd = new StringBuffer();
                    for (int i=0; i<browsers.length; i++)
                        cmd.append( (i==0  ? "" : " || " ) + browsers[i] +" \"" + url + "\" ");
                    try {
                        rt.exec(new String[] { "sh", "-c", cmd.toString() });
                    } catch (IOException ex) {
                        Logger.getLogger(BBJ.class.getName()).log(Level.SEVERE, null, ex);
                    }
                }
            }
        });

         
         
     }
     
     
     public void setupFonts(){
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

  
       JToolBar.Separator sep0 = new JToolBar.Separator(new Dimension(120,toolBar.getHeight()));
       toolBar.add(sep0);
       
       JToggleButton select_button = new JToggleButton();
       select_button.setIcon(new ImageIcon(BBJ.class.getResource("images/select.png")));
       toolBar.add(select_button);
       
       JToggleButton delete_button = new JToggleButton();
       delete_button.setIcon(new ImageIcon(BBJ.class.getResource("images/delete.png")));
       toolBar.add(delete_button);
 
       JToolBar.Separator sep1 = new JToolBar.Separator(new Dimension(20,toolBar.getHeight()));
       toolBar.add(sep1);
       
     /*  JToggleButton message_button = new JToggleButton();
       message_button.setIcon(new ImageIcon(BBJ.class.getResource("images/message_arrow.png")));
       toolBar.add(message_button);
       
       JToggleButton lifeline_button = new JToggleButton();
       lifeline_button.setIcon(new ImageIcon(BBJ.class.getResource("images/lifeline_arrow.png")));
       toolBar.add(lifeline_button);
       
       JToggleButton freecomment_button = new JToggleButton();
       freecomment_button.setIcon(new ImageIcon(BBJ.class.getResource("images/comment.png")));
       toolBar.add(freecomment_button);
       
       JToolBar.Separator sep2 = new JToolBar.Separator(new Dimension(20,toolBar.getHeight()));
       toolBar.add(sep2);
       */
       JButton undo_button = new JButton();
       undo_button.setIcon(new ImageIcon(BBJ.class.getResource("images/undo.png")));
       toolBar.add(undo_button);
       
       JButton redo_button = new JButton();
       redo_button.setIcon(new ImageIcon(BBJ.class.getResource("images/redo.png")));
       toolBar.add(redo_button);
   }
     
     /**
      *  Метод вызываемый при выборе меню "Сохранить как..."
      */
     private void saveFileUs () {
         
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
                String[] ps = ((FileNameExtensionFilter)chooser.getFileFilter()).getExtensions(); 
                filePath += ("." + ps[0]);
             }
            m_filename = filePath;
            try {
                try {
                    canvas.getModel().save(filePath);
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
    
    public void bindListeners(){
  
    
        
    }
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        app = new BBJ();
    }
}