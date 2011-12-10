/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.undoredo;

import bbj.graphicsobjects.Scene;
import bbj.graphicsobjects.SceneItem;
import java.awt.*;
import javax.swing.undo.AbstractUndoableEdit;
import javax.swing.undo.CannotUndoException;

/**
 *
 * @author Lemon
 */
public class MoveObjectEdit extends AbstractUndoableEdit {

    private Scene m_scene;
    private Point m_from;
    private Point m_to;
    private String m_describe;
    private SceneItem m_item;

  

    public MoveObjectEdit(Scene scene, SceneItem item, Point from, Point to) {
        m_scene = scene;
        m_from = from;
        m_to = to;
        m_item = item;

    }

    @Override
    public String getPresentationName() {
        m_describe = "Перемещение объекта";
        return m_describe;
    }

    @Override
    public void undo() throws CannotUndoException {

        super.undo();
        
  
        int index = m_scene.getGraphicsObjects().indexOf(m_item);
        m_scene.getGraphicsObjects().get(index).setLocation(m_from);
        m_scene.repaint();

    }

    @Override
    public void redo() throws CannotUndoException {

        super.redo();

        int index = m_scene.getGraphicsObjects().indexOf(m_item);
        m_scene.getGraphicsObjects().get(index).setLocation(m_to);
        m_scene.repaint();
    }
}
