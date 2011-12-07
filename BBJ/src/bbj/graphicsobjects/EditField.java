/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.graphicsobjects;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import javax.swing.JTextField;

/**
 * Класс, реализующий текстовое поле для ввода данных
 * @author Alexander
 */
public class EditField extends JTextField implements KeyListener{

    SceneItem m_item;   // Родительский элемент сцены
            
    /**
     * Конструктор с параметром
     * @param item Элемент сцены
     */
    EditField(SceneItem item){
        
        m_item = item;
        this.setBounds(5, 5, 120, 40);
        
        m_item.add(this);
        this.setVisible(true);
        this.grabFocus();

        String qwe = item.getText();
        this.setText(qwe);
        this.addKeyListener(this);
    }
    
    /**
     * Обработка события нажатия клавиш
     * @param e Данное событие
     */
    @Override
    public void keyTyped(KeyEvent e) {
        if (e.getKeyChar() == KeyEvent.VK_ENTER){   // Если нажали Enter
            
            // Изменить текст
            String qwe = this.getText();
            m_item.setText(qwe);
            m_item.updateUI();
            this.setVisible(false);
            m_item.remove(this);
        }
        else if (e.getKeyChar() == KeyEvent.VK_ESCAPE){ // Если нажали Escape
            this.setVisible(false);
            m_item.remove(this);
            m_item.updateUI();
        }
            
    }

    @Override
    public void keyPressed(KeyEvent e) {
        
    }

    @Override
    public void keyReleased(KeyEvent e) {

    }   
}
